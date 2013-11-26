/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualscore.h"

VisualScore::VisualScore(QObject *parent)
    : VisualItem(VisualItem::VisualScoreItem,
                 VisualItem::GraphicalRowType, parent),
      m_headerItem(0),
      m_footerItem(0)
{
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
