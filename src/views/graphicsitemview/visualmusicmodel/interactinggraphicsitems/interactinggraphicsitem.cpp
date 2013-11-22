/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "../iteminteraction.h"
#include "interactinggraphicsitem.h"

InteractingGraphicsItem::InteractingGraphicsItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_itemInteraction(0)
{
}

ItemInteraction *InteractingGraphicsItem::itemInteraction() const
{
    return m_itemInteraction;
}

void InteractingGraphicsItem::setItemInteraction(ItemInteraction *itemInteraction)
{
    if (itemInteraction == m_itemInteraction)
        return;

    if (m_itemInteraction)
        delete m_itemInteraction;

    itemInteraction->setParent(this);
    m_itemInteraction = itemInteraction;

    emit itemInteractionChanged();
}

void InteractingGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_itemInteraction)
        m_itemInteraction->mousePressEvent(event);
}

void InteractingGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_itemInteraction)
        m_itemInteraction->mouseMoveEvent(event);
}

void InteractingGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_itemInteraction)
        m_itemInteraction->mouseReleaseEvent(event);
}

void InteractingGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_itemInteraction)
        m_itemInteraction->mouseDoubleClickEvent(event);
}

void InteractingGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (m_itemInteraction)
        m_itemInteraction->contextMenuEvent(event);
}
