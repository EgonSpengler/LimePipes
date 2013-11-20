/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualmeasure.h"

VisualMeasure::VisualMeasure(QObject *parent)
    : VisualItem(parent)
{
}

VisualItem::ItemType VisualMeasure::itemType() const
{
    return VisualItem::VisualMeasureItem;
}

void VisualMeasure::setDataFromIndex(const QPersistentModelIndex &index)
{
}
