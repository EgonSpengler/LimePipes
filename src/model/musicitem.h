/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <Qt>
#include <QList>
#include <QMap>
#include <QVariant>

class QXmlStreamWriter;
class QXmlStreamReader;

class MusicItem
{
public:
    enum Type {
        RootItemType = 1,
        ScoreType,
        TuneType,
        PartType,
        MeasureType,
        SymbolType,
        NoItemType
    };

    explicit MusicItem(Type type=NoItemType, Type childType=NoItemType, MusicItem *parent=0);
    virtual ~MusicItem() { qDeleteAll(m_children); }

    Type type() const { return m_type; }
    Type childType() const { return m_childType; }

    MusicItem *parent() const { return m_parent; }
    void setParent(MusicItem *parent);

    bool hasChildren() const { return !m_children.isEmpty(); }
    bool insertChild(int row, MusicItem *item);
    bool addChild(MusicItem *item);
    void swapChildren(int oldRow, int newRow) { m_children.swap(oldRow, newRow); }
    int rowOfChild(MusicItem *item) const { return m_children.indexOf(item); }
    int childCount() const { return m_children.count(); }
    MusicItem *childAt(int row) const { return m_children.value(row); }
    MusicItem *takeChild(int row);
    QList<MusicItem*> children() const { return m_children; }
    virtual bool okToInsertChild(const MusicItem *item, int row) { Q_UNUSED(item) Q_UNUSED(row) return true; }

    QVariant data(int role = Qt::UserRole) const;
    bool setData(const QVariant &value, int role);
    const QMap<int, QVariant> itemData() const { return m_data; }

    virtual bool itemSupportsWritingOfData(int role) const = 0;
    virtual void writeItemDataToXmlStream(QXmlStreamWriter *writer) = 0;
    virtual void readCurrentElementFromXmlStream(QXmlStreamReader *reader) = 0;

protected:
    void initData(const QVariant &value, int role) { writeData(value, role); }
    virtual void beforeWritingData(QVariant &value, int role);
    virtual void afterWritingData(int role);
    Type m_type;
    Type m_childType;
    QMap<int, QVariant> m_data;

private:
    void writeData(const QVariant &value, int role);
    QList<MusicItem*> m_children;
    MusicItem *m_parent;
};

class NullMusicItem : public MusicItem
{
public:
    NullMusicItem()
        : MusicItem(MusicItem::NoItemType, MusicItem::NoItemType) {}
    NullMusicItem(const MusicItem &other)
    {
        m_type = other.type();
        m_childType = other.childType();
        m_data = other.itemData();
    }
    bool itemSupportsWritingOfData(int role) const { Q_UNUSED(role) return true; }
    void writeItemDataToXmlStream(QXmlStreamWriter *writer) { Q_UNUSED(writer) }
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader) { Q_UNUSED(reader) }
};

#endif // MUSICITEM_H
