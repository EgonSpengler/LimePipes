/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include <itemdatatypes.h>
#include "symbolgraphicsitem.h"

SymbolGraphicsItem::SymbolGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent)
{
}

void SymbolGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPen pen(Qt::red, 1);
//    painter->setPen(pen);

//    painter->drawRect(boundingRect());
//    painter->drawPixmap(0, 0, m_symbolGraphic->pixmap());
}

void SymbolGraphicsItem::setData(const QVariant &value, int key)
{
    if (key == LP::SymbolGraphic) {
        if (!value.isValid())
            return;

        m_symbolGraphic = value.value<SymbolGraphicPtr>();
    }
}
