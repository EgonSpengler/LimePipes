/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <itemdatatypes.h>
#include <datatypes/instrument.h>
#include <score.h>
#include <tune.h>
#include "tst_musicproxymodeltest.h"

Q_IMPORT_PLUGIN(MusicModelTestPlugin)

void MusicProxyModelTest::initTestcase()
{
    m_instrumentNames = m_sourceModel->instrumentNames();
    if (m_instrumentNames.isEmpty()) {
        qWarning("There was no plugin loaded by the model.");
        return;
    }

    m_symbolNames = m_sourceModel->symbolNamesForInstrument(m_instrumentNames.at(0));
    if (m_symbolNames.isEmpty()) {
        qWarning("Plugin's instrument has no symbols.");
        return;
    }
}

void MusicProxyModelTest::init()
{
    m_sourceModel = new MusicModel(this);
    m_proxyModel = new MusicProxyModel(this);
    m_proxyModel->setSourceModel(m_sourceModel);
}

void MusicProxyModelTest::cleanup()
{
    delete m_sourceModel;
}


void MusicProxyModelTest::testColumnCount()
{
    QVERIFY2(m_proxyModel->columnCount(QModelIndex()) == 3, "Fail, wrong column count");
}

void MusicProxyModelTest::testInsertScore()
{
    QModelIndex firstScore = m_proxyModel->insertScore(0, "First Title");
    QVERIFY2(m_proxyModel->rowCount(QModelIndex()) == 1, "Score was not inserted");
    QVERIFY2(firstScore.isValid(), "No valid Modelindex was returned while inserting score");
    QVERIFY2(firstScore.row() == 0, "Score was inserted in wrong row");
    QVERIFY2(firstScore.column() == 0, "Score was inserted in wrong column");
    QVERIFY2(m_proxyModel->data(firstScore, LP::ScoreTitle) == "First Title", "Failed score title");

    m_proxyModel->setData(firstScore, "Score 1", LP::ScoreTitle);
    QModelIndex secondScore = m_proxyModel->insertScore(m_proxyModel->rowCount(QModelIndex()), "Second Title");
    m_proxyModel->setData(secondScore, "Score 2", LP::ScoreTitle);
    QVERIFY2(secondScore.data(LP::ScoreTitle) == "Score 2", "Score 2's title isn't there");
    QVERIFY2(secondScore.row() == m_proxyModel->rowCount(QModelIndex()) - 1, "Score 2 was inserted in wrong row");
    QVERIFY2(secondScore.column() == 0, "Score 2 was inserted in wrong column");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_proxyModel, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    m_proxyModel->insertScore(-1, "Failed Score1");
    m_proxyModel->insertScore(5, "Failed Score2");

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicProxyModelTest::testAppendScore()
{
    QModelIndex firstScore = m_proxyModel->appendScore("First title");
    QVERIFY2(firstScore.isValid(), "Failed appending score");
    QVERIFY2(m_proxyModel->data(firstScore, LP::ScoreTitle) == "First title", "Failed getting title from appended score");
}

void MusicProxyModelTest::testInsertTuneIntoScore()
{
    QModelIndex score = m_proxyModel->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_proxyModel->insertTuneIntoScore(0, score, m_instrumentNames.at(0));
    InstrumentPtr instrument = m_proxyModel->data(tune, LP::TuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting instrument back");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_proxyModel, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    m_proxyModel->insertTuneIntoScore(-1, score, m_instrumentNames.at(0));
    m_proxyModel->insertTuneIntoScore(5, score, m_instrumentNames.at(0));

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicProxyModelTest::testAppendTuneToScore()
{
    QModelIndex score = m_proxyModel->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_proxyModel->appendTuneToScore(score, m_instrumentNames.at(0));
    InstrumentPtr instrument = m_proxyModel->data(tune, LP::TuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting instrument back");
}

void MusicProxyModelTest::testInsertTuneWithScore()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    InstrumentPtr instrument = m_proxyModel->data(tune, LP::TuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting score title from index");
    // New tune and new score => tune in row and column 0
    QVERIFY2(tune.column() == 0, "Tune is in wrong column");
    QVERIFY2(tune.row() == 0, "Tune is in wrong row");
}

void MusicProxyModelTest::testInsertSymbol()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_proxyModel->insertPartIntoTune(0, tune, 8);
    QModelIndex measure = m_proxyModel->index(0, 0, part);
    QModelIndex symbol1 = m_proxyModel->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));
    QVERIFY2(symbol1.isValid(), "Failed inserting symbol");
    QVERIFY2(m_proxyModel->data(symbol1, LP::SymbolName) == m_symbolNames.at(0), "Failed getting symbol's name");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_proxyModel, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    m_proxyModel->insertSymbolIntoMeasure(15, measure, m_symbolNames.at(0));
    m_proxyModel->insertSymbolIntoMeasure(-1, measure, m_symbolNames.at(0));

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted");
}

void MusicProxyModelTest::testCallOfOkToInsertChild()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_proxyModel->insertPartIntoTune(0, tune, 8);
    QModelIndex measure = m_proxyModel->index(0, 0, part);
    QModelIndex validSymbol = m_proxyModel->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));

    QVERIFY2(validSymbol.isValid(), "Failed inserting valid symbol");

    QModelIndex invalidSymbol = m_proxyModel->insertSymbolIntoMeasure(1, measure, "invalid symbol name");
    QVERIFY2(invalidSymbol.isValid() == false, "Failed. It was possible to insert a invalid symbol");
}

void MusicProxyModelTest::testItemForIndex()
{
    QModelIndex scoreIndex = m_proxyModel->insertScore(0, "Random Title");
    MusicItem *score = m_proxyModel->itemForIndex(scoreIndex);
    QVERIFY2(score->data(LP::ScoreTitle) == "Random Title", "Failed to get the correct item for an index");
}

void MusicProxyModelTest::testClear()
{
    m_proxyModel->insertScore(0, "Title");
    QVERIFY2(m_proxyModel->index(0, 0, QModelIndex()).isValid() == true, "At least one item should be in the model for next test");
    m_proxyModel->clear();
    QVERIFY2(m_proxyModel->index(0, 0, QModelIndex()).isValid() == false, "Model wasn't cleared");
}

void MusicProxyModelTest::testIsScore()
{
    QModelIndex firstScore = m_proxyModel->appendScore("First title");
    QVERIFY2(m_proxyModel->isIndexScore(firstScore), "Failed, should return true for score");
}

void MusicProxyModelTest::testIsTune()
{
    QModelIndex score = m_proxyModel->insertScore(0, "First Score");
    QModelIndex tune = m_proxyModel->appendTuneToScore(score, m_instrumentNames.at(0));
    QVERIFY2(m_proxyModel->isIndexTune(tune), "Faile, should return true for tune");
}

void MusicProxyModelTest::testIsSymbol()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_proxyModel->insertPartIntoTune(0, tune, 8);
    QModelIndex measure = m_proxyModel->index(0, 0, part);
    QModelIndex symbol1 = m_proxyModel->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));

    QVERIFY2(m_proxyModel->isIndexSymbol(symbol1), "Failed, should return true for symbol");
}

void MusicProxyModelTest::testPitchColumn()
{
    QModelIndex symbolWithPitch = symbolIndexWithData(LP::SymbolPitch);

    if (!symbolWithPitch.isValid())
        qWarning("Used instrument plugin supports no symbol with pitch");

    QModelIndex pitchIndex = m_proxyModel->sibling(symbolWithPitch.row(), MusicProxyModel::PitchColumn, symbolWithPitch);
    QVERIFY2(pitchIndex.isValid(), "Fail, pitch index isn't valid");

    QVariant pitchVariant = m_proxyModel->data(pitchIndex, LP::SymbolPitch);
    QVERIFY2(pitchVariant.canConvert<PitchPtr>(), "Pitch wasn't returned");
}

void MusicProxyModelTest::testLengthColumn()
{
    QModelIndex symbolWithLength = symbolIndexWithData(LP::SymbolLength);

    QModelIndex lengthIndex = m_proxyModel->sibling(symbolWithLength.row(), MusicProxyModel::LengthColumn, symbolWithLength);
    QVERIFY2(lengthIndex.isValid(), "Fail, length index isn't valid");

    QVariant lengthVariant = m_proxyModel->data(lengthIndex, LP::SymbolLength);
    QVERIFY2(lengthVariant.canConvert<Length::Value>(), "Length wasn't returnde");
}

QModelIndex MusicProxyModelTest::symbolIndexWithData(LP::SymbolDataRole role)
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_proxyModel->insertPartIntoTune(0, tune, 8);
    QModelIndex measure = m_proxyModel->index(0, 0, part);


    foreach (QString symbolName, m_symbolNames) {
        QModelIndex symbolIndex = m_proxyModel->insertSymbolIntoMeasure(0, measure, symbolName);
        QVariant dataVar = symbolIndex.data(role);
        if (dataVar.isValid()) {
            return symbolIndex;
        }
    }
    return QModelIndex();
}

QTEST_MAIN(MusicProxyModelTest)
