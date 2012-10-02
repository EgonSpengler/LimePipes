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
#include <itemdatatypes.h>
#include <interfaceglobals.h>

class SymbolTest : public QObject
{
    Q_OBJECT
    
public:
    SymbolTest(): m_symbol(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testType();
    void testChildType();
    void testDataPolicyForRole_data();
    void testDataPolicyForRole();
    void testSymbolType();

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

void SymbolTest::testConstructor()
{
    QVERIFY2(m_symbol->data(LP::symbolType).toInt() == LP::NoSymbolType, "Wrong Symbol id in default constructor");
    QVERIFY2(m_symbol->data(LP::symbolName).isValid(), "Symbol has no name in default constructor");

    Symbol symbol(333, "Testsymbol");
    QVERIFY2(symbol.data(LP::symbolType).toInt() == 333, "Failed setting symbol Id in constructor");
    QVERIFY2(symbol.data(LP::symbolName) == "Testsymbol", "Failed setting symbol name in constructor");
    QVERIFY2(symbol.data(Qt::DisplayRole) == "Testsymbol", "DisplayRole should equal name");
}

void SymbolTest::testType()
{
    QVERIFY2( m_symbol->type() == MusicItem::SymbolType, "Symbol returns the wrong type" );
}

void SymbolTest::testChildType()
{
    QVERIFY2( m_symbol->childType() == MusicItem::NoItemType, "The child itemtype of Symbol is not NoItem type");
}

void SymbolTest::testDataPolicyForRole_data()
{
    Symbol *symbol = new Symbol();
    QTest::addColumn<DataPolicy>("policy");
    QTest::addColumn<bool>("readable");
    QTest::addColumn<bool>("writable");

    QTest::newRow("display role")               << symbol->dataPolicyForRole(Qt::DisplayRole) << true << false;
    QTest::newRow("symbol name")                << symbol->dataPolicyForRole(LP::symbolName) << true << false;
    QTest::newRow("symbol type")                << symbol->dataPolicyForRole(LP::symbolType) << true << false;
    QTest::newRow("symbol length")              << symbol->dataPolicyForRole(LP::symbolLength) << false << false;
    QTest::newRow("symbol pitch")               << symbol->dataPolicyForRole(LP::symbolPitch) << false << false;
    delete symbol;
}

void SymbolTest::testDataPolicyForRole()
{
    QFETCH(DataPolicy, policy);
    QFETCH(bool, readable);
    QFETCH(bool, writable);

    QCOMPARE(policy.isReadable(), readable);
    QCOMPARE(policy.isWritable(), writable);

}

void SymbolTest::testSymbolType()
{
    QVERIFY2(m_symbol->symbolType() == LP::NoSymbolType, "Failed to get the default symbol type");
}

QTEST_APPLESS_MAIN(SymbolTest)

#include "tst_symboltest.moc"
