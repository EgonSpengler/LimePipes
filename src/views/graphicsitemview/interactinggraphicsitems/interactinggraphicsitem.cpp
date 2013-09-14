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

VisualItemInterface *InteractingGraphicsItem::visualItem() const
{
    return m_visualItem;
}

void InteractingGraphicsItem::setVisualItem(VisualItemInterface *visualItem)
{
    m_visualItem = visualItem;
}
