/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualsymbol.h"

VisualSymbol::VisualSymbol()
{
}


AbstractVisualItem::Type VisualSymbol::type() const
{
    return AbstractVisualItem::VisualSymbolItem;
}

void VisualSymbol::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualSymbol::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualSymbol::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualSymbol::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisualSymbol::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}
