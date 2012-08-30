/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicitem.h"

MusicItem::MusicItem(Type type, Type childType, MusicItem *parent)
    : m_type(type), m_childType(childType), m_parent(parent)
{
    if (m_parent)
        m_parent->addChild(this);
}

bool MusicItem::insertChild(int row, MusicItem *item)
{
    if (m_childType == NoItem)
        return false;

    if (m_childType == item->type()) {
        item->m_parent = this;
        m_children.insert(row, item);
        return true;
    }
    return false;
}

bool MusicItem::addChild(MusicItem *item)
{
    if (m_childType == NoItem)
        return false;

    if (m_childType == item->type()) {
        item->m_parent = this;
        m_children << item;
        return true;
    }
    return false;
}
