/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualsymbol.h"

VisualSymbol::VisualSymbol(QObject *parent)
    : VisualItem(VisualItem::VisualSymbolItem,
                 VisualItem::GraphicalInlineType, parent)
{
}
