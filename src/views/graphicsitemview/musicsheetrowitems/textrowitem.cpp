/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "textrowitem.h"
#include <QGraphicsSimpleTextItem>

#include <QPainter>


TextRowItem::TextRowItem(QGraphicsItem *parent)
    : PageContentRowItem(parent)
{
}

void TextRowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{
    painter->drawText(boundingRect(), "hallo welt");
}
