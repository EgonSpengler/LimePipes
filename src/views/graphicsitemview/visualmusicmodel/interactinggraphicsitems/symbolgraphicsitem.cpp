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
    QPixmap pixmap(m_symbolGraphic->pixmap());
//    painter->drawPixmap(0, 0, pixmap.scaled(pixmap.width(), 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    painter->drawPixmap(0, 0, pixmap);
}

void SymbolGraphicsItem::setData(const QVariant &value, int key)
{
    if (key == LP::SymbolGraphic) {
        if (!value.isValid())
            return;

        m_symbolGraphic = value.value<SymbolGraphicPtr>();
    }
}
