/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualmeasure.h"

VisualMeasure::VisualMeasure(QObject *parent)
    : VisualItem(VisualItem::VisualMeasureItem,
                 VisualItem::GraphicalInlineType, parent)
{
}
