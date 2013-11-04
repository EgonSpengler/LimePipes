/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include <symbol.h>
#include <tune.h>
#include <part.h>
#include <plugins/GreatHighlandBagpipe/greathighlandbagpipe.h>
#include "tst_measuretest.h"

MeasureTest::MeasureTest()
{
}

void MeasureTest::init()
{
    m_measure = new Measure();
    m_instrument = GreatHighlandBagpipe().instrument();
}

void MeasureTest::cleanup()
{
    delete m_measure;
}

void MeasureTest::testType()
{
    QVERIFY2(m_measure->type() == MusicItem::MeasureType, "Measure item returns the wrong type");
}

void MeasureTest::testChildType()
{
    QVERIFY2(m_measure->childType() == MusicItem::SymbolType, "The child itemtype of measure is not symbol type");
}

void MeasureTest::testOkToInsertChildRedefinition()
{
    // The test data. The two symbols should be one valid and one invalid type for the instrument
    Symbol *melodyNoteSymbol = new Symbol(LP::MelodyNote, "Melody Note");
    Symbol *invalidSymbol = new Symbol(LP::NoSymbolType, "Melody Note");

    // Tune with default instrument should always return false
    Q_ASSERT(m_measure->parent() == 0);
    QVERIFY2(m_measure->okToInsertChild(melodyNoteSymbol, 0) == false, "It's not ok to insert Symbol into a measure with no parent item");
    QVERIFY2(m_measure->okToInsertChild(invalidSymbol, 0) == false, "It's not ok to insert Symbol into a measure with no parent item");

    // Symbols should only be added, if measure has a parent part and that part a parent tune
    // with an instrument, that supports that symbols
    delete m_measure;

    Tune *tune = new Tune(m_instrument);
    Part *part = new Part(tune);
    m_measure  = new Measure(part);
    QVERIFY(m_measure->parent() == part);
    QVERIFY(part->parent() == tune);

    QVERIFY2(tune->data(LP::TuneInstrument).isValid() == true, "The next tests requires a Tune with instrument");
    QVERIFY2(m_instrument->supportsSymbolType(LP::MelodyNote) == m_measure->okToInsertChild(melodyNoteSymbol, 0),
             "Measure doesn't return the same as the instrument for a valid symbol");
    QVERIFY2(m_instrument->supportsSymbolType(LP::NoSymbolType) == m_measure->okToInsertChild(invalidSymbol, 0),
             "Measure doesn't return the same as the instrument for a invalid symbol");
}

QTEST_MAIN(MeasureTest)

#include "tst_measuretest.moc"
