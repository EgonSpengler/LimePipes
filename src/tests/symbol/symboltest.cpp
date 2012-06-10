/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "symboltest.h"
#include "model/symbol.h"

void SymbolTest::testType()
{
    Symbol symbol;
    QVERIFY2( symbol.type() == SymbolType, "Symbol returns the wrong type" );
}
