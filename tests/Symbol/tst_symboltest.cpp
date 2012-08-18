/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <symbol.h>

class SymbolTest : public QObject
{
    Q_OBJECT
    
public:
    SymbolTest(): m_symbol(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testParentType();

private:
    Symbol *m_symbol;
};

void SymbolTest::testType()
{
    QVERIFY2( m_symbol->type() == SymbolType, "Symbol returns the wrong type" );
}

void SymbolTest::testParentType()
{
    QVERIFY2( m_symbol->parentType() == TuneType, "The parent itemtype of Symbol is not TuneType");
}

void SymbolTest::init()
{
    m_symbol = new Symbol();
}

void SymbolTest::cleanup()
{
    delete m_symbol;
}

QTEST_APPLESS_MAIN(SymbolTest)

#include "tst_symboltest.moc"
