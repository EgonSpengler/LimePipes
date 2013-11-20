/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualpart.h"

VisualPart::VisualPart(QObject *parent)
    : VisualItem(parent)
{
}

VisualItem::ItemType VisualPart::itemType() const
{
    return VisualItem::VisualPartItem;
}

void VisualPart::setDataFromIndex(const QPersistentModelIndex &index)
{
}
