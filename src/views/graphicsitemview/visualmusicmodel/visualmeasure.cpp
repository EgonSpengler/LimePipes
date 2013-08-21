/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualmeasure.h"

VisualMeasure::VisualMeasure()
{
}

AbstractVisualItem::Type VisualMeasure::type() const
{
    return AbstractVisualItem::VisualMeasureItem;
}

void VisualMeasure::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualMeasure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualMeasure::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualMeasure::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualMeasure::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}
