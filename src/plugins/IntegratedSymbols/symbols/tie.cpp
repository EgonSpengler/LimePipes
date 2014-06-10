/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/defines.h>
#include "tie.h"

Tie::Tie()
    : Symbol(LP::Tie, tr("Tie"))
{
    initSymbol();
}

void Tie::initSymbol()
{
    initData(QVariant::fromValue<SymbolCategory>(SymbolCategory::Spanning), LP::SymbolCategory);
}

bool Tie::itemSupportsWritingOfData(int role) const
{
    if (role == LP::SymbolSpanType) {
        return true;
    }
    return Symbol::itemSupportsWritingOfData(role);
}
