/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicitem.h"
#include <itembehaviorfactory.h>

MusicItem::MusicItem(ItemBehavior::Type type, MusicItem *parent)
    : m_parent(parent),
      m_behavior(ItemBehaviorFactory::getBehavior(type))
{
    if (m_parent)
        m_parent->addChild(this);
}

bool MusicItem::insertChild(int row, MusicItem *item)
{
    if (m_behavior->childType() == ItemBehavior::NoItem)
        return false;

    if (m_behavior->childType() == item->type()) {
        item->m_parent = this;
        m_children.insert(row, item);
        return true;
    }
    return false;
}

bool MusicItem::addChild(MusicItem *item)
{
    if (m_behavior->childType() == ItemBehavior::NoItem)
        return false;

    if (m_behavior->childType() == item->type()) {
        item->m_parent = this;
        m_children << item;
        return true;
    }
    return false;
}

QVariant MusicItem::data(int role)
{
    if (m_behavior)
        return m_behavior->data(role);
    return QVariant();
}

bool MusicItem::setData(const QVariant &value, int role)
{
    if (m_behavior)
        return m_behavior->setData(value, role);
    else
        return false;
}
