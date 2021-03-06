/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_ghb_plugintest.h"

void GHB_PluginTest::init()
{
    m_bagpipe = new GreatHighlandBagpipe();
}

void GHB_PluginTest::cleanup()
{
    delete m_bagpipe;
}

void GHB_PluginTest::testCreate()
{
    GreatHighlandBagpipe bagpipe;
    Q_UNUSED(bagpipe)
}

void GHB_PluginTest::testName()
{
    GreatHighlandBagpipe bagpipe;
    QVERIFY2( bagpipe.name().isEmpty() == false, "Got empty string as Instrument name" );
}

void GHB_PluginTest::testInstrumentID()
{
    GreatHighlandBagpipe bagpipe;
    QVERIFY2( bagpipe.instrument()->type() == LP::GreatHighlandBagpipe, "Failed getting the right instrument ID for the Great Highland Bagpipe");
}

void GHB_PluginTest::testsupportedSymbolTypes()
{
    QVERIFY2(m_bagpipe->instrument()->supportsSymbolType(LP::NoSymbolType) == false, "Fail Bagpipe Instrument does support NoSymbolType");
    QVERIFY2(m_bagpipe->instrument()->supportsSymbolType(LP::MelodyNote), "Failed Bagpipe Instrument does not support melody notes");
    QVERIFY2(m_bagpipe->instrument()->supportsSymbolType(GHB::Doubling), "Failed Bagpipe Instrument does not support doublings");
}

void GHB_PluginTest::testSymbolNamesForAllSymbols()
{
    QStringList allSymbols = m_bagpipe->symbolNames();

    Symbol *symbol = 0;
    foreach (QString symbolName, allSymbols) {
        symbol = m_bagpipe->getSymbolForName(symbolName);
        QVERIFY2(symbol->data(LP::SymbolName) == symbolName, "Failed, Symbol's name returned by Plugin doesn't match with name parameter from getSymbol-method.");
        delete symbol;
    }
}

void GHB_PluginTest::testPitchContext()
{
    PitchContextPtr pitchContext = m_bagpipe->instrument()->pitchContext();
    QVERIFY2(pitchContext->pitchForStaffPos(-2)->name() == "High A", "Failed High A");
    QVERIFY2(pitchContext->pitchForStaffPos(-1)->name() == "High G", "Failed High G");
    QVERIFY2(pitchContext->pitchForStaffPos(0)->name() == "F", "Failed F");
    QVERIFY2(pitchContext->pitchForStaffPos(1)->name() == "E", "Failed E");
    QVERIFY2(pitchContext->pitchForStaffPos(2)->name() == "D", "Failed D");
    QVERIFY2(pitchContext->pitchForStaffPos(3)->name() == "C", "Failed C");
    QVERIFY2(pitchContext->pitchForStaffPos(4)->name() == "B", "Failed B");
    QVERIFY2(pitchContext->pitchForStaffPos(5)->name() == "Low A", "Failed Low A");
    QVERIFY2(pitchContext->pitchForStaffPos(6)->name() == "Low G", "Failed Low G");
}

void GHB_PluginTest::testStaffType()
{
    QVERIFY2(m_bagpipe->instrument()->staffType() == StaffType::Standard,
             "Wrong staff type from great highland bagpipe instrument");
}

QTEST_MAIN(GHB_PluginTest)

#include "tst_ghb_plugintest.moc"
