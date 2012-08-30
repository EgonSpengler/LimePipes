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
    void testChildType();

private:
    Symbol *m_symbol;
};

void SymbolTest::init()
{
    m_symbol = new Symbol();
}

void SymbolTest::cleanup()
{
    delete m_symbol;
}

void SymbolTest::testType()
{
    QVERIFY2( m_symbol->type() == MusicItem::Symbol, "Symbol returns the wrong type" );
}

void SymbolTest::testChildType()
{
    QVERIFY2( m_symbol->childType() == MusicItem::NoItem, "The child itemtype of Symbol is not NoItem type");
}

QTEST_APPLESS_MAIN(SymbolTest)

#include "tst_symboltest.moc"
