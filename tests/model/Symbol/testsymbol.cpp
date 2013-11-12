/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testsymbol.h"

TestSymbol::TestSymbol(QObject *parent) :
    QObject(parent)
{
    setSymbolOptions(Symbol::HasPitch |
                     Symbol::HasLength);
    initData(QVariant::fromValue<Length::Value>(Length::_16), LP::SymbolLength);
}
