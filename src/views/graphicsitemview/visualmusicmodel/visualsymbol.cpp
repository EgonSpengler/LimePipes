/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualsymbol.h"

VisualSymbol::VisualSymbol(QObject *parent)
    : AbstractVisualItem(parent)
{
}

AbstractVisualItem::Type VisualSymbol::type() const
{
    return AbstractVisualItem::VisualSymbolItem;
}

void VisualSymbol::setDataFromIndex(const QPersistentModelIndex &index)
{
}
