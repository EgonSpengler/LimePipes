/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualitem.h"

VisualItem::VisualItem(QObject *parent)
    : QObject(parent),
      m_itemType(NoVisualItem),
      m_graphicalItemType(NoGraphicalType)
{
}

VisualItem::VisualItem(ItemType type, QObject *parent)
    : QObject(parent),
      m_itemType(type),
      m_graphicalItemType(NoGraphicalType)
{
}

VisualItem::VisualItem(VisualItem::ItemType type, VisualItem::GraphicalType graphicalType, QObject *parent)
    : QObject(parent),
      m_itemType(type),
      m_graphicalItemType(graphicalType)
{
}

void VisualItem::setInlineGraphic(InteractingGraphicsItem *inlineGraphic)
{
    if (graphicalType() != GraphicalInlineType)
        return;

    if (inlineGraphic == 0) return;

    if (m_graphicsItems.count())
        m_graphicsItems.clear();

    m_graphicsItems.append(inlineGraphic);
}

InteractingGraphicsItem *VisualItem::inlineGraphic() const
{
    if (!m_graphicsItems.count() == 1)
        return 0;

    return m_graphicsItems.at(0);
}
