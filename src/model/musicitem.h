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
#include <itembehavior.h>

class MusicItem
{
public:
    MusicItem(MusicItem *parent=0);
    ~MusicItem() { qDeleteAll(m_children); delete m_behavior; }
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
    void setBehavior(ItemBehavior* behavoir);
    virtual int type() const { return m_behavior ? m_behavior->type() : ItemBehavior::RootItemType; }
    virtual int childType() const { return m_behavior ? m_behavior->childType() : ItemBehavior::ScoreType; }
    virtual QVariant data(int role = Qt::UserRole);
    virtual bool setData(const QVariant &value, int role);

private:
    QList<MusicItem*> m_children;
    MusicItem *m_parent;
    ItemBehavior *m_behavior;
};

#endif // MUSICITEM_H
