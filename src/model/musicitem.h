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

class MusicItem
{
public:
    MusicItem(MusicItem *parent=0);
    ~MusicItem() { qDeleteAll(m_children); }
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

    void insertChild(int row, MusicItem *item)
        { item->m_parent = this; m_children.insert(row, item); }
    void addChild(MusicItem *item)
        { item->m_parent = this; m_children << item; }
    void swapChildren(int oldRow, int newRow)
        { m_children.swap(oldRow, newRow); }
    virtual int type() const { return -1; }
    virtual int parentType() const { return -1; }
    virtual QVariant data(int role = Qt::UserRole);

    void setName(const QString &name)
        { m_name = name; }
    QString name() const
        { return m_name; }

private:
    QList<MusicItem*> m_children;
    MusicItem *m_parent;
    QString m_name;
};

#endif // MUSICITEM_H
