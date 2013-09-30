/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualmeasure.h"

VisualMeasure::VisualMeasure(QObject *parent)
    : QObject(parent)
{
}

AbstractVisualItem::Type VisualMeasure::type() const
{
    return AbstractVisualItem::VisualMeasureItem;
}

void VisualMeasure::setDataFromIndex(const QPersistentModelIndex &index)
{
}
