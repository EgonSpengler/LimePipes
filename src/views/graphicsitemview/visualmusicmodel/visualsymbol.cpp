/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualsymbol.h"

VisualSymbol::VisualSymbol(QObject *parent)
    : VisualItem(parent)
{
}

VisualItem::ItemType VisualSymbol::itemType() const
{
    return VisualItem::VisualSymbolItem;
}

void VisualSymbol::setDataFromIndex(const QPersistentModelIndex &index)
{
}
