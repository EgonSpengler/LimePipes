/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "interactinggraphicsitems/interactinggraphicsitem.h"
#include "iteminteraction.h"
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

    connectItemInteraction(inlineGraphic->itemInteraction());
    m_graphicsItems.append(inlineGraphic);
}

void VisualItem::connectItemInteraction(ItemInteraction *itemInteraction)
{
    if (itemInteraction == 0)
        return;

    connect(itemInteraction, &ItemInteraction::dataChanged,
            this, &VisualItem::dataChanged);
}

void VisualItem::disconnectItemInteraction(ItemInteraction *itemInteraction)
{
    if (itemInteraction == 0)
        return;

    disconnect(itemInteraction, &ItemInteraction::dataChanged,
               this, &VisualItem::dataChanged);
}

InteractingGraphicsItem *VisualItem::inlineGraphic() const
{
    if (!m_graphicsItems.count() == 1)
        return 0;

    return m_graphicsItems.at(0);
}

void VisualItem::appendRow(InteractingGraphicsItem *graphicsItem)
{
    if (graphicalType() != GraphicalRowType)
        return;

    if (graphicsItem == 0) return;

    connectItemInteraction(graphicsItem->itemInteraction());
    m_graphicsItems.append(graphicsItem);

    emit rowSequenceChanged();
}

void VisualItem::removeLastRow()
{
    if (graphicalType() != GraphicalRowType)
        return;

    if (m_graphicsItems.isEmpty())
        return;

    InteractingGraphicsItem *graphicsItem = m_graphicsItems.takeLast();
    disconnectItemInteraction(graphicsItem->itemInteraction());

    emit rowSequenceChanged();
}

QList<InteractingGraphicsItem *> VisualItem::rowGraphics() const
{
    return m_graphicsItems;
}

int VisualItem::rowCount() const
{
    if (graphicalType() == GraphicalInlineType)
        return 0;

    return m_graphicsItems.count();
}

void VisualItem::setData(const QVariant &value, int key)
{
    foreach (InteractingGraphicsItem *graphicsItem, m_graphicsItems) {
        graphicsItem->setData(value, key);
    }
}

void VisualItem::insertChildItem(int index, VisualItem *childItem)
{
    Q_UNUSED(index);
    Q_UNUSED(childItem);
}
