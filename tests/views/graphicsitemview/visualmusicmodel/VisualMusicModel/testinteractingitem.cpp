/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testinteractingitem.h"

TestInteractingItem::TestInteractingItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent)
{
}

void TestInteractingItem::insertChildItem(int index, InteractingGraphicsItem *childItem)
{
    emit insertChildItemCalled();
}

void TestInteractingItem::setData(const QVariant &value, int key)
{
    InteractingGraphicsItem::setData(value, key);
    emit setDataCalled();
}
