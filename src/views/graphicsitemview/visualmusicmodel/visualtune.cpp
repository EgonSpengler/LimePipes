/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualtune.h"

VisualTune::VisualTune()
{
}

AbstractVisualItem::Type VisualTune::type() const
{
    return AbstractVisualItem::VisualTuneItem;
}

void VisualTune::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualTune::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualTune::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualTune::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualTune::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}
