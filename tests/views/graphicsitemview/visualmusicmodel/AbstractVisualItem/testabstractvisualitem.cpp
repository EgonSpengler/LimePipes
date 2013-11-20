/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testabstractvisualitem.h"

TestAbstractVisualItem::TestAbstractVisualItem()
{
}

VisualItem::ItemType TestAbstractVisualItem::itemType() const
{
    return VisualItem::VisualRootItem;
}

void TestAbstractVisualItem::setDataFromIndex(const QPersistentModelIndex &index)
{
}
