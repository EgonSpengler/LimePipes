/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <tune.h>
#include <symbol.h>
#include <greathighlandbagpipe.h>

class TuneTest : public QObject
{
    Q_OBJECT
    
public:
    TuneTest()
        : m_tune(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testType();
    void testChildType();
    void testSetInstrument();
    void testSetInstrumentDisplayRole();
    void testOkToInsertChildRedefinition();
    void testSetData();

private:
    Tune *m_tune;
    Instrument *m_instrument;
};

void TuneTest::init()
{
    m_tune = new Tune();
    m_instrument = GreatHighlandBagpipe().instrument();
}

void TuneTest::cleanup()
{
    delete m_tune;
    delete m_instrument;
}

void TuneTest::testConstructor()
{
    // Tune with default instrument
    QVERIFY2(m_tune->instrument()->name() == Instrument().name(), "Failed to set Instrument in default constructor");

    delete m_tune;
    m_tune = new Tune(m_instrument);
    QVERIFY2(m_tune->instrument()->name() == m_instrument->name(), "Failed to set Instrument in constructor");
    QVERIFY2(m_tune->type() == MusicItem::TuneType, "Tune returns the wrong type");
    QVERIFY2(m_tune->childType() == MusicItem::SymbolType, "The child itemtype of tune is wrong");
}

void TuneTest::testType()
{
    QVERIFY2(m_tune->type() == MusicItem::TuneType, "Tune returns the wrong type after default constructor");
}

void TuneTest::testChildType()
{
    QVERIFY2(m_tune->childType() == MusicItem::SymbolType, "The child itemtype of tune is not Symbol type");
}

void TuneTest::testSetInstrument()
{
    m_tune->setInstrument(m_instrument);
    QVERIFY2(m_tune->instrument()->type() == LP::GreatHighlandBagpipe, "Failed set and get instrument");
}

void TuneTest::testSetInstrumentDisplayRole()
{
    m_tune->setInstrument(m_instrument);
    QVERIFY2(m_tune->data(Qt::DisplayRole) == m_instrument->name() + " tune", "Failed setting display role");
}

void TuneTest::testOkToInsertChildRedefinition()
{
    // The test data. The two symbols should be one valid and one invalid type for the instrument
    Symbol *melodyNoteSymbol = new Symbol(LP::MelodyNote, "Melody Note");
    Symbol *invalidSymbol = new Symbol(LP::NoSymbolType, "Melody Note");

    // Tune with default instrument should always return false
    QVERIFY2(m_tune->okToInsertChild(melodyNoteSymbol) == false, "It's not ok to insert Symbol into a tune with default instrument");
    QVERIFY2(m_tune->okToInsertChild(invalidSymbol) == false, "It's not ok to insert Symbol into a tune with default instrument");

    // Tune with instrument should return the same as the instrument
    m_tune->setInstrument(m_instrument);
    QVERIFY2(m_tune->data(LP::tuneInstrument).isValid() == true, "The next tests requires a Tune with instrument");
    QVERIFY2(m_instrument->supportsSymbolType(LP::MelodyNote) == m_tune->okToInsertChild(melodyNoteSymbol),
             "Tune doesn't return the same as the instrument for a valid symbol");
    QVERIFY2(m_instrument->supportsSymbolType(LP::NoSymbolType) == m_tune->okToInsertChild(invalidSymbol),
             "Tune doesn't return the same as the instrument for a invalid symbol");
}

void TuneTest::testSetData()
{
    m_tune->data(Qt::DisplayRole);
}

QTEST_APPLESS_MAIN(TuneTest)

#include "tst_tunetest.moc"
