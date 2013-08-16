/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualscore.h"

VisualScore::VisualScore()
{
}


AbstractVisualItem::Type VisualScore::type() const
{
    return AbstractVisualItem::VisualScoreItem;
}

void VisualScore::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualScore::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualScore::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualScore::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualScore::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}
