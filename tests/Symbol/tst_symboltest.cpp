/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "symbol.h"

class SymbolTest : public QObject
{
    Q_OBJECT
    
public:
    SymbolTest();
    
private Q_SLOTS:
    void testType();
};

SymbolTest::SymbolTest()
{
}

void SymbolTest::testType()
{
    Symbol symbol;
    QVERIFY2( symbol.type() == SymbolType, "Symbol returns the wrong type" );
}

QTEST_APPLESS_MAIN(SymbolTest)

#include "tst_symboltest.moc"
