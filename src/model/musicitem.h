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
    MusicItem(ItemBehavior::Type type, MusicItem *parent=0);
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

    bool insertChild(int row, MusicItem *item);
    bool addChild(MusicItem *item);
    void swapChildren(int oldRow, int newRow)
        { m_children.swap(oldRow, newRow); }
    virtual ItemBehavior::Type type() const { return m_behavior->type(); }
    virtual ItemBehavior::Type childType() const { return m_behavior->childType(); }
    virtual QVariant data(int role = Qt::UserRole);
    virtual bool setData(const QVariant &value, int role);

private:
    QList<MusicItem*> m_children;
    MusicItem *m_parent;
    ItemBehavior *m_behavior;
};

#endif // MUSICITEM_H
