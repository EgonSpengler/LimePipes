/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/defines.h>
#include "tie.h"

Tie::Tie(const QString &name)
    : Symbol(LP::Tie, name)
{
    initSymbol();
}

void Tie::initSymbol()
{
}

bool Tie::itemSupportsWritingOfData(int role) const
{
    switch (role) {
    case LP::SymbolSpanBuddy:
    case LP::SymbolSpanType:
        return true;
    }

    return Symbol::itemSupportsWritingOfData(role);
}
