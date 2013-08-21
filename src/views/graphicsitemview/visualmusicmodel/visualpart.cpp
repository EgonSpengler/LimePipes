/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualpart.h"

VisualPart::VisualPart()
{
}

AbstractVisualItem::Type VisualPart::type() const
{
    return AbstractVisualItem::VisualPartItem;
}

void VisualPart::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualPart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualPart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualPart::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualPart::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}
