/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPen>
#include <QPainter>
#include "measuregraphicsitem.h"

MeasureGraphicsItem::MeasureGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent)
{
}


void MeasureGraphicsItem::insertChildItem(int index, InteractingGraphicsItem *childItem)
{
}

void MeasureGraphicsItem::setData(const QVariant &value, int key)
{
}


void MeasureGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPen pen(Qt::blue, 1);
//    painter->setPen(pen);

//    painter->drawRect(boundingRect());
}
