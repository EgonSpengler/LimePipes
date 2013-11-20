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


VisualItem::ItemType VisualRootItem::itemType() const
{
    return VisualItem::VisualRootItem;
}

void VisualRootItem::setDataFromIndex(const QPersistentModelIndex &index)
{
}
