/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicitem.h"

MusicItem::MusicItem(MusicItem *parent)
    : m_parent(parent),
      m_behavior(new ItemBehavior(ItemBehavior::RootItemType, ItemBehavior::ScoreType))
{
    if (m_parent)
        m_parent->addChild(this);
}

void MusicItem::setBehavior(ItemBehavior *behavoir)
{
    if (m_behavior)
        delete m_behavior;
    m_behavior = behavoir;
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
