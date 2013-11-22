/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualscore.h"

VisualScore::VisualScore(QObject *parent)
    : VisualItem(parent),
      m_headerItem(0),
      m_footerItem(0)
{
}

VisualItem::ItemType VisualScore::itemType() const
{
    return VisualItem::VisualScoreItem;
}

InteractingGraphicsItem *VisualScore::headerItem() const
{
    return m_headerItem;
}

void VisualScore::setFooterItem(InteractingGraphicsItem *item)
{
    m_footerItem = item;
}

void VisualScore::setHeaderItem(InteractingGraphicsItem *item)
{
    m_headerItem = item;
}

InteractingGraphicsItem *VisualScore::footerItem() const
{
    return m_footerItem;
}

VisualItem::GraphicalType VisualScore::graphicalType() const
{
    return VisualItem::GraphicalRowType;
}

QList<InteractingGraphicsItem *> VisualScore::rowGraphics() const
{
    QList<InteractingGraphicsItem *> items;
    items << m_headerItem;
    items << m_footerItem;
    return items;
}
