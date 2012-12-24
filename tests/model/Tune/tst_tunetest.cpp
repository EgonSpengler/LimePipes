/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QXmlStreamWriter>
#include <symbol.h>
#include <symbols/barline.h>
#include <plugins/GreatHighlandBagpipe/greathighlandbagpipe.h>
#include "tst_tunetest.h"

void TuneTest::init()
{
    m_tune = new Tune();
    m_instrument = GreatHighlandBagpipe().instrument();
}

void TuneTest::cleanup()
{
    delete m_tune;
}

void TuneTest::testConstructor()
{
    InstrumentPtr instrument = m_tune->instrument();
    QVERIFY2(instrument != 0, "Failed default tune has no instrument");

    // Tune with default instrument
    QVERIFY2(instrument->name() == NullInstrument().name(), "Failed to set Instrument in default constructor");

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

void TuneTest::testOkToInsertChildRedefinition()
{
    // The test data. The two symbols should be one valid and one invalid type for the instrument
    Symbol *melodyNoteSymbol = new Symbol(LP::MelodyNote, "Melody Note");
    Symbol *invalidSymbol = new Symbol(LP::NoSymbolType, "Melody Note");

    // Tune with default instrument should always return false
    QVERIFY2(m_tune->okToInsertChild(melodyNoteSymbol, 0) == false, "It's not ok to insert Symbol into a tune with default instrument");
    QVERIFY2(m_tune->okToInsertChild(invalidSymbol, 0) == false, "It's not ok to insert Symbol into a tune with default instrument");

    // BarLine symbol should always return true
    BarLine *barLine = new BarLine(BarLine::StartPart);
    QVERIFY2(m_tune->okToInsertChild(barLine, 0), "A Single BarLine should not be insertable");
    delete barLine;

    // Tune with instrument should return the same as the instrument
    // only after a part was added
    delete m_tune;
    m_tune = new Tune(m_instrument);
    QVERIFY2(m_tune->data(LP::tuneInstrument).isValid() == true, "The next tests requires a Tune with instrument");
    QVERIFY2(m_instrument->supportsSymbolType(LP::MelodyNote) == m_tune->okToInsertChild(melodyNoteSymbol, 0),
             "Tune doesn't return the same as the instrument for a valid symbol");
    QVERIFY2(m_instrument->supportsSymbolType(LP::NoSymbolType) == m_tune->okToInsertChild(invalidSymbol, 0),
             "Tune doesn't return the same as the instrument for a invalid symbol");
}

void TuneTest::testSetData()
{
    m_tune->data(Qt::DisplayRole);
}

void TuneTest::testWriteToXmlStream()
{
    delete m_tune;
    m_tune = new Tune(m_instrument);
    QString data;
    QXmlStreamWriter writer(&data);
    QString instrumentTag = QString("<instrument>") += m_instrument->name();

    m_tune->writeItemDataToXmlStream(&writer);
    QVERIFY2(!data.contains(instrumentTag, Qt::CaseInsensitive), "Instrument tag was found");
}

void TuneTest::testRowOfPartStart()
{
    QVERIFY2(m_tune->startRowOfPart(2) == 0, "Wrong row returned for empty tune");
    m_tune->addChild(new BarLine(BarLine::StartPart)); // Part 0 - Row 0
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine(BarLine::EndPart));
    m_tune->addChild(new BarLine(BarLine::StartPart)); // Part 1 - Row 5
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine(BarLine::EndPart));
    m_tune->addChild(new BarLine(BarLine::StartPart)); // Part 2 - Row 10
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine());
    m_tune->addChild(new BarLine(BarLine::EndPart)); // Appended part - Row 15

    QVERIFY2(m_tune->startRowOfPart(-1) == 0, "Wrong row for negative part number");
    QVERIFY2(m_tune->startRowOfPart(0) == 0, "Wrong row for part number 0");
    QVERIFY2(m_tune->startRowOfPart(1) == 5, "Wrong row for part number 1");
    QVERIFY2(m_tune->startRowOfPart(2) == 10, "Wrong row for part number 2");
    QVERIFY2(m_tune->startRowOfPart(3) == 15, "Wrong row for part number 3");
    QVERIFY2(m_tune->startRowOfPart(5) == 15, "Wrong row for part number higher than max parts");
}

QTEST_APPLESS_MAIN(TuneTest)

#include "tst_tunetest.moc"
