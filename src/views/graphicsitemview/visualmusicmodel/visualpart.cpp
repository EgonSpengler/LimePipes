/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualpart.h"

VisualPart::VisualPart(QObject *parent)
    : VisualItem(VisualItem::VisualPartItem,
                 VisualItem::GraphicalRowType,
                 parent)
{
}
