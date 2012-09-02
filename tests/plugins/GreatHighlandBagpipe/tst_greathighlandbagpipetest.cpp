/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <interfaceglobals.h>

#include <greathighlandbagpipe.h>


class GreatHighlandBagpipeTest : public QObject
{
    Q_OBJECT
    
public:
    GreatHighlandBagpipeTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testCreate();
    void testName();
    void testInstrumentID();
    void testsupportedSymbolTypes();

private:
    GreatHighlandBagpipe *m_bagpipe;
};

GreatHighlandBagpipeTest::GreatHighlandBagpipeTest()
{
}

void GreatHighlandBagpipeTest::init()
{
    m_bagpipe = new GreatHighlandBagpipe();
}

void GreatHighlandBagpipeTest::cleanup()
{
    delete m_bagpipe;
}

void GreatHighlandBagpipeTest::testCreate()
{
    GreatHighlandBagpipe bagpipe;
    Q_UNUSED(bagpipe)
}

void GreatHighlandBagpipeTest::testName()
{
    GreatHighlandBagpipe bagpipe;
    QVERIFY2( bagpipe.name().isEmpty() == false, "Got empty string as Instrument name" );
}

void GreatHighlandBagpipeTest::testInstrumentID()
{
    GreatHighlandBagpipe bagpipe;
    QVERIFY2( bagpipe.instrument()->type() == LP::GreatHighlandBagpipe, "Failed getting the right instrument ID for the Great Highland Bagpipe");
}

void GreatHighlandBagpipeTest::testsupportedSymbolTypes()
{
    QVERIFY2(m_bagpipe->instrument()->supportsSymbolType(LP::NoSymbolType) == false, "Fail Bagpipe Instrument does support NoSymbolType");
    QVERIFY2(m_bagpipe->instrument()->supportsSymbolType(LP::MelodyNote), "Failed Bagpipe Instrument does not support melody notes");
    QVERIFY2(m_bagpipe->instrument()->supportsSymbolType(LP::Bar), "Failed Bagpipe Instrument oes not support bar");
}

QTEST_APPLESS_MAIN(GreatHighlandBagpipeTest)

#include "tst_greathighlandbagpipetest.moc"
