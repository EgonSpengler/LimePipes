/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualrootitem.h"

VisualRootItem::VisualRootItem()
{
}


AbstractVisualItem::Type VisualRootItem::type() const
{
    return AbstractVisualItem::VisualRootItem;
}

void VisualRootItem::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualRootItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualRootItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualRootItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualRootItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}
