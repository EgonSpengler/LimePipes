/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QList>
#include <QVariant>
#include <QString>
#include <QMap>
#include <datapolicy.h>

class MusicItem
{
public:
    enum Type {
        RootItemType = 1,
        ScoreType,
        TuneType,
        SymbolType,
        NoItemType
    };

    explicit MusicItem(Type type=NoItemType, Type childType=NoItemType, MusicItem *parent=0);
    virtual ~MusicItem() { qDeleteAll(m_children); }
    MusicItem *parent() const
        { return m_parent; }
    MusicItem *childAt(int row) const
        { return m_children.value(row); }
    int rowOfChild(MusicItem *item) const
        { return m_children.indexOf(item); }
    int childCount() const
        { return m_children.count(); }
    bool hasChildren() const
        { return !m_children.isEmpty(); }
    QList<MusicItem*> children() const
        { return m_children; }

    bool insertChild(int row, MusicItem *item);
    bool addChild(MusicItem *item);
    void swapChildren(int oldRow, int newRow)
        { m_children.swap(oldRow, newRow); }
    Type type() const
        { return m_type; }
    Type childType() const
        { return m_childType; }
    QVariant data(int role = Qt::UserRole) const;
    void setData(const QVariant &value, int role);
    virtual bool okToInsertChild( const MusicItem *item )
        { Q_UNUSED(item) return true; }
    virtual const DataPolicy dataPolicyForRole(int role) const = 0;

protected:
    virtual QVariant readData(int role) const
        { return m_data.value(role); }
    void initData(const QVariant &value, int role)
        { writeData(value, role); }
    QMap<int, QVariant> m_data;

private:
    int getDataRoleForAccess(int role, DataPolicy policy) const;
    void writeData(const QVariant &value, int role)
       { m_data.insert(role, value); }
    QList<MusicItem*> m_children;
    const Type m_type;
    const Type m_childType;
    MusicItem *m_parent;
};

#endif // MUSICITEM_H
