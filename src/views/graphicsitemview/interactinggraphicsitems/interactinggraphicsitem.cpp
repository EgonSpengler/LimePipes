/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "interactinggraphicsitem.h"

InteractingGraphicsItem::InteractingGraphicsItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_visualItem(0)
{
}

InteractingItemInterface *InteractingGraphicsItem::interactingItem() const
{
    return m_visualItem;
}

void InteractingGraphicsItem::setInteractingItem(InteractingItemInterface *visualItem)
{
    m_visualItem = visualItem;
}

void InteractingGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_visualItem)
        m_visualItem->mousePressEvent(event);
}

void InteractingGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_visualItem)
        m_visualItem->mouseMoveEvent(event);
}

void InteractingGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_visualItem)
        m_visualItem->mouseReleaseEvent(event);
}

void InteractingGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_visualItem)
        m_visualItem->mouseDoubleClickEvent(event);
}
