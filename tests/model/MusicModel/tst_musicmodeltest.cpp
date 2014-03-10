/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QDir>
#include <QtTest/QSignalSpy>
#include <QMetaType>
#include <QStack>
#include <QTemporaryFile>
#include <QUndoStack>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QXmlStreamReader>
#include <utilities/error.h>
#include "qt_modeltest/modeltest.h"
#include <utilities/error.h>
#include <common/itemdataroles.h>
#include <common/datatypes/instrument.h>
#include <symbol.h>
#include <score.h>
#include <tune.h>
#include "tst_musicmodeltest.h"

Q_IMPORT_PLUGIN(MusicModelTestPlugin)

namespace {

const int CompressionLevelOfMimeData = 9;
const QString ScoreMimeType  = "application/vnd.limepipes.xml.score.z";
const QString TuneMimeType   = "application/vnd.limepipes.xml.tune.z";
const QString SymbolMimeType = "application/vnd.limepipes.xml.symbol.z";

}

void MusicModelTest::initTestcase()
{
    m_instrumentNames = m_model->instrumentNames();
    if (m_instrumentNames.isEmpty()) {
        qWarning("There was no plugin loaded by the model.");
        return;
    }

    m_symbolNames = m_model->symbolNamesForInstrument(m_instrumentNames.at(0));
    if (m_symbolNames.isEmpty()) {
        qWarning("Plugin's instrument has no symbols.");
        return;
    }

    m_musicItemTagNames = QStringList() << "SCORE" << "TUNE" << "SYMBOL" << "LIMEPIPES";
}

void MusicModelTest::cleanupTestcase()
{
}

void MusicModelTest::init()
{
    m_model = new MusicModel(this);
}

void MusicModelTest::cleanup()
{
    delete m_model;
}

void MusicModelTest::testColumnCount()
{
    QVERIFY2(m_model->columnCount(QModelIndex()) == 1, "Wrong column count");
}

void MusicModelTest::testInsertScore()
{
    QModelIndex firstScore = m_model->insertScore(0, "First Title");
    QVERIFY2(m_model->rowCount(QModelIndex()) == 1, "Score was not inserted");
    QVERIFY2(firstScore.isValid(), "No valid Modelindex was returned while inserting score");
    QVERIFY2(firstScore.row() == 0, "Score was inserted in wrong row");
    QVERIFY2(firstScore.column() == 0, "Score was inserted in wrong column");
    QVERIFY2(m_model->data(firstScore, LP::ScoreTitle) == "First Title", "Failed score title");

    m_model->setData(firstScore, "Score 1", LP::ScoreTitle);
    QModelIndex secondScore = m_model->insertScore(m_model->rowCount(QModelIndex()), "Second Title");
    m_model->setData(secondScore, "Score 2", LP::ScoreTitle);
    QVERIFY2(secondScore.data(LP::ScoreTitle) == "Score 2", "Score 2's title isn't there");
    QVERIFY2(secondScore.row() == m_model->rowCount(QModelIndex()) - 1, "Score 2 was inserted in wrong row");
    QVERIFY2(secondScore.column() == 0, "Score 2 was inserted in wrong column");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy rowsInsertedSpy(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    m_model->insertScore(-1, "Failed Score1");
    m_model->insertScore(5, "Failed Score2");

    QVERIFY2(rowsInsertedSpy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicModelTest::testAppendScore()
{
    QModelIndex firstScore = m_model->appendScore("First title");
    QVERIFY2(firstScore.isValid(), "Failed appending score");
    QVERIFY2(m_model->data(firstScore, LP::ScoreTitle) == "First title", "Failed getting title from appended score");
}

void MusicModelTest::testSetData()
{
    QString testTitle("Test title");
    QString testTitleSetData("Test title new");
    LP::ScoreDataRole testDataRole = LP::ScoreTitle;
    QModelIndex scoreIndex = m_model->appendScore(testTitle);
    QSignalSpy dataChangedSpy(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)));

    m_model->setData(scoreIndex, testTitleSetData, testDataRole);
    QVERIFY2(dataChangedSpy.count() == 1, "Data changed signal wasn't emitted");
    QList<QVariant> parameter = dataChangedSpy.takeFirst();
    Q_ASSERT(parameter.count() == 3);
    QVariant rolesVariant = parameter.at(2);
    Q_ASSERT(rolesVariant.canConvert<QVector<int>>());
    QVector<int> roles = rolesVariant.value<QVector<int>>();
    QVERIFY2(roles.count() == 1, "Empty roles list was emitted");
    QVERIFY2(roles.at(0) == static_cast<int>(testDataRole),
             "Wrong role was emitted");

    // Setting the same data, signal must not be emitted
    m_model->setData(scoreIndex, testTitleSetData, testDataRole);
    QVERIFY2(dataChangedSpy.count() == 0, "Data changed signal was emitted despite non changing data");

    // Setting wrong data role, signal must also not be emitted
    m_model->setData(scoreIndex, testTitleSetData, LP::TuneInstrument);
    QVERIFY2(dataChangedSpy.count() == 0, "Data changed signal was emitted with wrong data role");
}

void MusicModelTest::testInsertTuneIntoScore()
{
    QModelIndex score = m_model->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_model->insertTuneIntoScore(0, score, m_instrumentNames.at(0));
    InstrumentPtr instrument = m_model->data(tune, LP::TuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting instrument back");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    m_model->insertTuneIntoScore(-1, score, m_instrumentNames.at(0));
    m_model->insertTuneIntoScore(5, score, m_instrumentNames.at(0));

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicModelTest::testAppendTuneToScore()
{
    QModelIndex score = m_model->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_model->appendTuneToScore(score, m_instrumentNames.at(0));
    InstrumentPtr instrument = m_model->data(tune, LP::TuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting instrument back");
}

void MusicModelTest::testInsertTuneWithScore()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    InstrumentPtr instrument = m_model->data(tune, LP::TuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Failed getting score title from index");
    // New tune and new score => tune in row and column 0
    QVERIFY2(tune.column() == 0, "Tune is in wrong column");
    QVERIFY2(tune.row() == 0, "Tune is in wrong row");
}

void MusicModelTest::testInsertPartIntoTune()
{
    int measureCount = 12;
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->insertPartIntoTune(0, tune, measureCount, true);

    QVERIFY2(part.isValid(), "Failed inserting Part into Tune");
    QVERIFY2(m_model->rowCount(part) != 0, "No measures were inserted");
    QVERIFY2(m_model->rowCount(part) == measureCount, "Not the correct count of measures were inserted");
    QVERIFY2(part.data(LP::PartRepeat).toBool() == true, "Wrong part repeat value returned");

    // Check if staff type was taken from tune's instrument and saved into part
    InstrumentPtr instrument = tune.data(LP::TuneInstrument).value<InstrumentPtr>();
    StaffType staffType = part.data(LP::PartStaffType).value<StaffType>();
    QVERIFY2(instrument->staffType() == staffType, "Part has no staff type set");
}

void MusicModelTest::testAppendPartIntoTune()
{
    int measureCount = 12;
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->appendPartToTune(tune, measureCount, true);

    QVERIFY2(part.isValid(), "Failed appending Part to Tune");
    QVERIFY2(m_model->rowCount(part) != 0, "No measures were inserted");
    QVERIFY2(m_model->rowCount(part) == 12, "Not the correct count of measures were inserted");
    QVERIFY2(part.data(LP::PartRepeat).toBool() == true, "Wrong part repeat value returned");

    // Check if staff type was taken from tune's instrument and saved into part
    InstrumentPtr instrument = tune.data(LP::TuneInstrument).value<InstrumentPtr>();
    StaffType staffType = part.data(LP::PartStaffType).value<StaffType>();
    QVERIFY2(instrument->staffType() == staffType, "Part has no staff type set");
}

void MusicModelTest::testInsertMeasureIntoPart()
{
    int measureCount = 8;
    int measureInsertPos = 4;
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->appendPartToTune(tune, measureCount, true);
    QModelIndex measure = m_model->insertMeasureIntoPart(measureInsertPos, part);

    QVERIFY2(measure.isValid(), "Failed inserting measure into part");
    QVERIFY2(measure.row() == measureInsertPos, "Measure was inserted in wrong place");
    QVERIFY2(m_model->rowCount(part) == measureCount + 1, "Measure not inserted in right part");
}

void MusicModelTest::testAppendMeasureToPart()
{
    int measureCount = 8;
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->appendPartToTune(tune, measureCount, true);
    QModelIndex measure = m_model->appendMeasureToPart(part);

    QVERIFY2(measure.isValid(), "Failed appending measure to part");
    QVERIFY2(measure.row() == m_model->rowCount(part) - 1, "Measure was not appended at end");
    QVERIFY2(m_model->rowCount(part) == measureCount + 1, "Measure not appended in right part");
}

void MusicModelTest::testInsertSymbolIntoMeasure()
{
    int measureCount = 8;
    int measureInsertPos = 4;
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->appendPartToTune(tune, measureCount, true);
    QModelIndex measure = m_model->insertMeasureIntoPart(measureInsertPos, part);
    QModelIndex symbol = m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));

    QVERIFY2(symbol.isValid(), "Failed inserting symbol into measure");
    QVERIFY2(m_model->rowCount(measure) == 1, "Failed inserting symbol into right measure");
    QVERIFY2(symbol.data(LP::SymbolName) == m_symbolNames.at(0), "Failed inserting right symbol with name");
}

void MusicModelTest::testAppendSymbolToMeasure()
{
    int measureCount = 8;
    int measureInsertPos = 4;
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->appendPartToTune(tune, measureCount, true);
    QModelIndex measure = m_model->insertMeasureIntoPart(measureInsertPos, part);
    QModelIndex symbol = m_model->appendSymbolToMeasure(measure, m_symbolNames.at(0));

    QVERIFY2(symbol.isValid(), "Failed inserting symbol into measure");
    QVERIFY2(m_model->rowCount(measure) == 1, "Failed inserting symbol into right measure");
    QVERIFY2(symbol.data(LP::SymbolName) == m_symbolNames.at(0), "Failed inserting right symbol with name");
}

void MusicModelTest::testFlags()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex score = m_model->index(0, 0, QModelIndex());
    QModelIndex part = m_model->insertPartIntoTune(0, tune, 9);
    QModelIndex measure = part.child(1, 0);
    QModelIndex symbol = m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));

    Q_ASSERT(tune.isValid());
    Q_ASSERT(score.isValid());
    Q_ASSERT(part.isValid());
    Q_ASSERT(measure.isValid());
    Q_ASSERT(symbol.isValid());


    Qt::ItemFlags scoreFlags = m_model->flags(score);
    QVERIFY2(scoreFlags.testFlag(Qt::ItemIsEnabled),     "Score is not enabled");
    QVERIFY2(scoreFlags.testFlag(Qt::ItemIsSelectable),  "Score is not selectable");
    QVERIFY2(scoreFlags.testFlag(Qt::ItemIsEditable),    "Score is not editable");
    QVERIFY2(scoreFlags.testFlag(Qt::ItemIsDragEnabled), "Score is not drag enabled");
    QVERIFY2(scoreFlags.testFlag(Qt::ItemIsDropEnabled), "Score is not drop enabled");

    Qt::ItemFlags tuneFlags = m_model->flags(tune);
    QVERIFY2(tuneFlags.testFlag(Qt::ItemIsEnabled),     "Tune is not enabled");
    QVERIFY2(tuneFlags.testFlag(Qt::ItemIsSelectable),  "Tune is not selectable");
    QVERIFY2(tuneFlags.testFlag(Qt::ItemIsEditable),    "Tune is not editable");
    QVERIFY2(tuneFlags.testFlag(Qt::ItemIsDragEnabled), "Tune is not drag enabled");
    QVERIFY2(tuneFlags.testFlag(Qt::ItemIsDropEnabled), "Tune is not drop enabled");

    Qt::ItemFlags partFlags = m_model->flags(part);
    QVERIFY2(partFlags.testFlag(Qt::ItemIsEnabled),     "Part is not enabled");
    QVERIFY2(partFlags.testFlag(Qt::ItemIsSelectable),  "Part is not selectable");
    QVERIFY2(partFlags.testFlag(Qt::ItemIsEditable),    "Part is not editable");
    QVERIFY2(partFlags.testFlag(Qt::ItemIsDragEnabled), "Part is not drag enabled");
    QVERIFY2(partFlags.testFlag(Qt::ItemIsDropEnabled),  "Part is not drop enabled");

    Qt::ItemFlags measureFlags = m_model->flags(measure);
    QVERIFY2(measureFlags.testFlag(Qt::ItemIsEnabled),      "Measure is not enabled");
    QVERIFY2(measureFlags.testFlag(Qt::ItemIsSelectable),   "Measure is not selectable");
    QVERIFY2(measureFlags.testFlag(Qt::ItemIsEditable),     "Measure is not editable");
    QVERIFY2(measureFlags.testFlag(Qt::ItemIsDragEnabled),  "Measure is not drag enabled");
    QVERIFY2(measureFlags.testFlag(Qt::ItemIsDropEnabled),  "Measure is not drop enabled");

    Qt::ItemFlags symbolFlags = m_model->flags(symbol);
    QVERIFY2(symbolFlags.testFlag(Qt::ItemIsEnabled),       "Symbol is not enabled");
    QVERIFY2(symbolFlags.testFlag(Qt::ItemIsSelectable),    "Symbol is not selectable");
    QVERIFY2(symbolFlags.testFlag(Qt::ItemIsEditable),      "Symbol is not editable");
    QVERIFY2(symbolFlags.testFlag(Qt::ItemIsDragEnabled),   "Symbol is not drag enabled");
    QVERIFY2(symbolFlags.testFlag(Qt::ItemIsDropEnabled),   "Symbol is not drop enabled");
}

void MusicModelTest::testCallOfOkToInsertChild()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->insertPartIntoTune(0, tune, 9);
    QModelIndex measure = m_model->insertMeasureIntoPart(1, part);

    QModelIndex validSymbol = m_model->appendSymbolToMeasure(measure, m_symbolNames.at(0));
    QVERIFY2(validSymbol.isValid(), "Failed inserting valid symbol");

    QModelIndex invalidSymbol = m_model->appendSymbolToMeasure(measure, "invalid symbol name");
    QVERIFY2(invalidSymbol.isValid() == false, "Failed. It was possible to insert an invalid symbol name");
}

void MusicModelTest::testQAbstractItemModelImplementation()
{
    for (int i=0; i < 3; i++) {
        m_model->insertScore(0, "Score Title");
    }

    QModelIndex secondScore = m_model->index(1, 0, QModelIndex());
    QVERIFY2(secondScore.isValid(), "Failed getting valid score");

    QModelIndex tune1 = m_model->insertTuneIntoScore(0, secondScore, m_instrumentNames.at(0));
    m_model->insertTuneIntoScore(0, secondScore, m_instrumentNames.at(0));

    QModelIndex part = m_model->insertPartIntoTune(0, tune1, 9);
    QModelIndex measure = m_model->index(2, 0, part);

    m_model->appendSymbolToMeasure(measure, m_symbolNames.at(0));

    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));
    m_model->insertSymbolIntoMeasure(1, measure, m_symbolNames.at(0));
    m_model->insertSymbolIntoMeasure(2, measure, m_symbolNames.at(0));
    m_model->insertSymbolIntoMeasure(1, measure, m_symbolNames.at(0));

    ModelTest * modelTest = new ModelTest(m_model, this);
    delete modelTest;
}

void MusicModelTest::testItemForIndex()
{
    QModelIndex scoreIndex = m_model->insertScore(0, "Random Title");
    MusicItem *score = m_model->itemForIndex(scoreIndex);
    QVERIFY2(score->data(LP::ScoreTitle) == "Random Title", "Failed to get the correct item for an index");
}

void MusicModelTest::testIndexForItem()
{
    MusicItem *score = 0;
    MusicItem *tune = 0;
    MusicItem *part = 0;
    MusicItem *measure = 0;
    MusicItem *symbol = 0;

    QModelIndex scoreIndex = m_model->appendScore("Title of score");
    score = m_model->itemForIndex(scoreIndex);
    Q_ASSERT(score);

    QModelIndex tuneIndex = m_model->insertTuneIntoScore(0, scoreIndex, m_instrumentNames.at(0));
    tune = m_model->itemForIndex(tuneIndex);
    Q_ASSERT(tune);

    QModelIndex partIndex = m_model->insertPartIntoTune(0, tuneIndex, 5);
    part = m_model->itemForIndex(partIndex);
    Q_ASSERT(part);

    QModelIndex measureIndex = m_model->index(2, 0, partIndex);
    measure = m_model->itemForIndex(measureIndex);
    Q_ASSERT(measure);

    QModelIndex symbolIndex = m_model->insertSymbolIntoMeasure(0, measureIndex, m_symbolNames.at(0));
    symbol = m_model->itemForIndex(symbolIndex);
    Q_ASSERT(symbol);

    QVERIFY2(m_model->itemForIndex(scoreIndex) == score, "Failed getting score item 1");
    QVERIFY2(m_model->itemForIndex(tuneIndex) == tune, "Failed getting tune item 1");
    QVERIFY2(m_model->itemForIndex(partIndex) == part, "Failed getting part item 1");
    QVERIFY2(m_model->itemForIndex(measureIndex) == measure, "Failed getting measure item 1");
    QVERIFY2(m_model->itemForIndex(symbolIndex) == symbol, "Failed getting symbol item 1");

    scoreIndex = m_model->appendScore("Title of second score");
    score = m_model->itemForIndex(scoreIndex);
    Q_ASSERT(score);

    tuneIndex = m_model->appendTuneToScore(scoreIndex, m_instrumentNames.at(0));
    tune = m_model->itemForIndex(tuneIndex);
    Q_ASSERT(tune);

    partIndex = m_model->insertPartIntoTune(0, tuneIndex, 5);
    part = m_model->itemForIndex(partIndex);
    Q_ASSERT(part);

    measureIndex = m_model->index(2, 0, partIndex);
    measure = m_model->itemForIndex(measureIndex);
    Q_ASSERT(measure);

    symbolIndex = m_model->insertSymbolIntoMeasure(1, measureIndex, m_symbolNames.at(0));
    symbol = m_model->itemForIndex(symbolIndex);
    Q_ASSERT(symbol);

    QVERIFY2(m_model->itemForIndex(scoreIndex) == score, "Failed getting score item 2");
    QVERIFY2(m_model->itemForIndex(tuneIndex) == tune, "Failed getting tune item 2");
    QVERIFY2(m_model->itemForIndex(partIndex) == part, "Failed getting part item 2");
    QVERIFY2(m_model->itemForIndex(measureIndex) == measure, "Failed getting measure item 2");
    QVERIFY2(m_model->itemForIndex(symbolIndex) == symbol, "Failed getting symbol item 2");
}

void MusicModelTest::testClear()
{
    m_model->insertScore(0, "Title");
    QVERIFY2(m_model->index(0, 0, QModelIndex()).isValid() == true, "At least one item should be in the model for next test");
    m_model->clear();
    QVERIFY2(m_model->index(0, 0, QModelIndex()).isValid() == false, "Model wasn't cleared");
}

void MusicModelTest::testIsScore()
{
    QModelIndex firstScore = m_model->appendScore("First title");
    QVERIFY2(m_model->isIndexScore(firstScore), "Failed, should return true for score");
}

void MusicModelTest::testIsTune()
{
    QModelIndex score = m_model->insertScore(0, "First Score");
    QModelIndex tune = m_model->appendTuneToScore(score, m_instrumentNames.at(0));
    QVERIFY2(m_model->isIndexTune(tune), "Faile, should return true for tune");
}

void MusicModelTest::testIsSymbol()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->appendPartToTune(tune, 10);
    QModelIndex measure = m_model->insertMeasureIntoPart(0, part);
    QModelIndex symbol1 = m_model->appendSymbolToMeasure(measure, m_symbolNames.at(0));
    QVERIFY2(m_model->isIndexSymbol(symbol1), "Failed, should return true for symbol");
}

void MusicModelTest::testSetColumnCount()
{
    QVERIFY2(m_model->columnCount(QModelIndex()) == 1, "Default column count wasn't 1");
    m_model->setColumnCount(4);
    QVERIFY2(m_model->columnCount(QModelIndex()) == 4, "Can't set column count");
}

void MusicModelTest::testRemoveInvalidRows()
{
    int scoreCount = 5;
    Q_ASSERT(scoreCount > 3);
    for (int i=0; i<scoreCount; i++) {
        m_model->appendScore("Score");
    }

    Q_ASSERT(m_model->rowCount(QModelIndex()) == scoreCount);

    QVERIFY2(m_model->removeRows(-1, 1, QModelIndex()) == false, "It is possible to remove rows with negative index");
    QVERIFY2(m_model->removeRows(scoreCount, 1, QModelIndex()) == false, "It is possible to remove row one row past last row");

    QVERIFY2(m_model->removeRows(scoreCount -2, 3, QModelIndex()) == false, "It is possible to remove row past last row");
    QVERIFY2(m_model->removeRows(scoreCount -2, 2, QModelIndex()) == true, "Remove from middle to end is not possible");
}

void MusicModelTest::testRemoveRows()
{
    int measureCount = 10;
    int measureNr    =  3;  // Measure number for model index
    QString symbolNameWithLength = "Testsymbol with pitch and length";
    int indexOfTestsymbol = m_symbolNames.indexOf(symbolNameWithLength);
    Q_ASSERT(indexOfTestsymbol != -1);
    Q_UNUSED(indexOfTestsymbol)

    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->insertPartIntoTune(0, tune, measureCount);
    QModelIndex measure = part.child(measureNr, 0);

    QModelIndex symbol1 = m_model->appendSymbolToMeasure(measure, symbolNameWithLength);
    m_model->setData(symbol1, Length::_1, LP::SymbolLength);
    QModelIndex symbol2 = m_model->appendSymbolToMeasure(measure, symbolNameWithLength);
    m_model->setData(symbol2, Length::_2, LP::SymbolLength);
    QModelIndex symbol3 = m_model->appendSymbolToMeasure(measure, symbolNameWithLength);
    m_model->setData(symbol3, Length::_4, LP::SymbolLength);

    // Removing Symbols
    QModelIndex thirdSymbol = m_model->index(2, 0, measure);
    Q_ASSERT(thirdSymbol.isValid());
    Length::Value lengthOfThirdSymbol = m_model->data(thirdSymbol, LP::SymbolLength).value<Length::Value>();

    QVERIFY2(m_model->removeRows(0, 2, measure), "Remove rows returned false");

    QVERIFY2(m_model->rowCount(measure) == 1, "Wrong row count after removing rows from measure");

    QModelIndex lastRemainingSymbol = m_model->index(0, 0, measure);
    Q_ASSERT(thirdSymbol.isValid());

    Length::Value lengthOfLastRemaining = m_model->data(lastRemainingSymbol, LP::SymbolLength).value<Length::Value>();

    QVERIFY2(lengthOfThirdSymbol == lengthOfLastRemaining, "Length value of last remaining symbol is wrong");

    // Removing Tune
    m_model->insertTuneIntoScore(1, m_model->index(0, 0, QModelIndex()), m_instrumentNames.at(0));
    QModelIndex scoreIndex1 = m_model->index(0, 0, QModelIndex());
    QVERIFY2(m_model->rowCount(scoreIndex1) == 2, "Not two tunes in score");
    m_model->removeRows(1, 1, scoreIndex1);
    QVERIFY2(m_model->rowCount(scoreIndex1) == 1, "Tune wasn't removed");

    // Removing Scores
    m_model->insertScore(1, "Second Score");
    m_model->insertScore(2, "Third score");
    m_model->insertScore(3, "Fourth score");
    QString titleOfScoreInRow0 = m_model->data(m_model->index(0, 0, QModelIndex()), LP::ScoreTitle).toString();
    Q_ASSERT(!titleOfScoreInRow0.isEmpty());
    QString titleOfScoreInRow3 = m_model->data(m_model->index(3, 0, QModelIndex()), LP::ScoreTitle).toString();
    Q_ASSERT(!titleOfScoreInRow3.isEmpty());

    m_model->removeRows(1, 2, QModelIndex());
    QVERIFY2(m_model->rowCount(QModelIndex()) == 2, "Failed removing scores");
    QString newTitleOfScoreInRow0 = m_model->data(m_model->index(0, 0, QModelIndex()), LP::ScoreTitle).toString();
    QString newTitleOfScoreInRow1 = m_model->data(m_model->index(1, 0, QModelIndex()), LP::ScoreTitle).toString();
    QVERIFY2(newTitleOfScoreInRow0 == titleOfScoreInRow0, "Title of score in row 0 is wrong");
    QVERIFY2(newTitleOfScoreInRow1 == titleOfScoreInRow3, "Title of score in row 1 is wrong");
}

void MusicModelTest::testSave()
{
#ifdef Q_OS_MAC
    QSKIP("Test hangs up on QXmlSchema::load() und OS X");
#endif
    QTemporaryFile tempFile;
    tempFile.open();
    QStack<QStringRef> musicItemTagStack;

    Q_ASSERT(!tempFile.fileName().isEmpty());

    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->insertPartIntoTune(0, tune, 10);
    QModelIndex measure = m_model->index(3, 0, part);

    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));
    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));

    tune = m_model->insertTuneWithScore(0, "Second Score", m_instrumentNames.at(0));
    part = m_model->insertPartIntoTune(0, tune, 10);
    measure = m_model->index(3, 0, part);
    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));
    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));


    try {
        Q_ASSERT(tempFile.isOpen());
        m_model->save(tempFile.fileName());
    }
    catch (LP::Error &error){
        qWarning() << "Failed saving: " << error.what();
    }

    QXmlStreamReader reader(&tempFile);

    // Check nesting of items
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (isMusicItemTag(reader.name())) {
                if (musicItemTagStack.count())
                    checkTagHierarchy(musicItemTagStack.top(), reader.name());
                musicItemTagStack.push(reader.name());
            }
        }
        if (reader.isEndElement()) {
            if (isMusicItemTag(reader.name())) {
                QVERIFY2(musicItemTagStack.pop() == reader.name(), "Music items are not correctly nested");
            }
        }
    }
    QString errorMessage = QString("Error occured while reading saved xml file: ") + reader.errorString();
    QVERIFY2(!reader.hasError(), errorMessage.toUtf8());

    // Check for instrument and symbol name attribute
    tempFile.reset();
    reader.setDevice(&tempFile);
    while (!reader.atEnd()) {
        reader.readNext();
        if (reader.isStartElement()) {
            if (reader.name() == "TUNE") {
                QVERIFY2(reader.attributes().hasAttribute("INSTRUMENT"), "Tune has no instrument attribute");
                QVERIFY2(reader.attributes().value("INSTRUMENT") == m_instrumentNames.at(0), "Tune returned wrong instrument name");
            }
            if (reader.name() == "SYMBOL") {
                QVERIFY2(reader.attributes().hasAttribute("NAME"), "Symbol has no name attribute");
                QVERIFY2(!reader.attributes().value("NAME").isEmpty(), "Symbol name was empty");
            }
        }
        if (reader.isEndElement()) {

        }
    }
    errorMessage = QString("Error occured while reading saved xml file for attribute check: ") + reader.errorString();
    QVERIFY2(!reader.hasError(), errorMessage.toUtf8());
}

bool MusicModelTest::isMusicItemTag(const QStringRef &tagName)
{
    QString tag = QString().append(tagName);
    return m_musicItemTagNames.contains(tag, Qt::CaseInsensitive);
}

void MusicModelTest::checkTagHierarchy(const QStringRef &parentTag, const QStringRef &tag)
{
    QString parentTagStr = QString().append(parentTag);
    QString tagStr = QString().append(tag);

    if (parentTagStr.compare("LIMEPIPES", Qt::CaseInsensitive) == 0) {
        QVERIFY2(tagStr.compare("SCORE", Qt::CaseInsensitive) == 0, "Failed, tag can't be under LIMEPIPES tag");
    }

    if (parentTagStr.compare("SCORE", Qt::CaseInsensitive) == 0) {
        QVERIFY2(tagStr.compare("TUNE", Qt::CaseInsensitive) == 0, "Failed, tag can't be under SCORE tag");
    }

    if (parentTagStr.compare("TUNE", Qt::CaseInsensitive) == 0) {
        QVERIFY2(tagStr.compare("SYMBOL", Qt::CaseInsensitive) == 0, "Failed, tag can't be under TUNE tag");
    }
}

QFileInfoList MusicModelTest::fileInfosForPatternList(const QStringList &patterns)
{
    QDir testFileDir( TESTFILE_DIRECTORY );
    Q_ASSERT(testFileDir.exists());
    return testFileDir.entryInfoList(patterns, QDir::Files);
}

void MusicModelTest::testXsdFile()
{
#ifdef Q_OS_MAC
    QSKIP("Test hangs up on QXmlSchema::load() und OS X");
#endif
    QVERIFY2(QFile::exists(LIMEPIPES_XSD_FILE), "XSD file doesn't exist");
    QUrl xsdUrl = QUrl::fromLocalFile(LIMEPIPES_XSD_FILE);
    QXmlSchema schema;
    schema.load(xsdUrl);
    QVERIFY2(schema.isValid(), "Schema file is not valid");
}

void MusicModelTest::checkTestfilesAgainstXsd()
{
#ifdef Q_OS_MAC
    QSKIP("Test hangs up on QXmlSchema::load() und OS X");
#endif
    QSKIP("Checks require long time", SkipSingle);

    QUrl xsdUrl = QUrl::fromLocalFile(LIMEPIPES_XSD_FILE);
    QXmlSchema schema;
    schema.load(xsdUrl);
    QXmlSchemaValidator validator(schema);

    // Valid files
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_*.lime");
    foreach (QFileInfo fileInfo, fileInfos) {
        QFile file(fileInfo.absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        QString message("Valid document is invalid: ");
        message += fileInfo.fileName();
        QVERIFY2(validator.validate(&file, QUrl::fromLocalFile(file.fileName())), message.toLatin1().data());
        qDebug() << "File: " << fileInfo.fileName() << " is valid";
        file.close();
    }

    // Invalid files
    fileInfos = fileInfosForPatternList(QStringList() << "invalid_*.lime");
    foreach (QFileInfo fileInfo, fileInfos) {
        QFile file(fileInfo.absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        QString message("Invalid document is valid: ");
        message += fileInfo.fileName();
        QVERIFY2(validator.validate(&file, QUrl::fromLocalFile(file.fileName())) == false, message.toLatin1().data());
        qDebug() << "File: " << fileInfo.fileName() << " is invalid";
        file.close();
    }
}

void MusicModelTest::testInvalidDocuments()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_document*.lime");

    foreach (QFileInfo file, fileInfos) {
        checkForScoreCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::testValidMinimalDocuments()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_document_minimal*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForScoreCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::testValidDocumentThreeScores()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_document_three_scores*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForScoreCount(file.absoluteFilePath(), 3);
    }
}

void MusicModelTest::checkForScoreCount(const QString &filename, int count)
{
    loadModel(filename);
    int scoreCount = m_model->rowCount(QModelIndex());
    QString message = QString("Wrong count of scores loaded (") + QString::number(scoreCount) + " scores) from file: " + filename;
    QVERIFY2(scoreCount == count, message.toUtf8());
}

void MusicModelTest::testInvalidScoreTuneWithNoInstrument()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_score_tune_has_no_instrument.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForTuneCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::testInvalidScoreWrongItemsUnderScore()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_score_wrong_items_under_score.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForTuneCount(file.absoluteFilePath(), 0);
    }
}

//! Test file with one tune more than maximum tunes under score
void MusicModelTest::testInvalidScoreFourValidTunes()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_score_four_valid_tunes.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForTuneCount(file.absoluteFilePath(), 3);
    }
}

void MusicModelTest::testValidScoreThreeValidTunes()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_score_three*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForTuneCount(file.absoluteFilePath(), 3);
    }
}

void MusicModelTest::checkForTuneCount(const QString &filename, int count)
{
    loadModel(filename);
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());

    int tuneCount = -1;
    Q_ASSERT(scoreIndex.isValid());
    tuneCount = m_model->rowCount(scoreIndex);

    QString message = QString("Wrong count of tunes loaded (" + QString::number(tuneCount) + " tunes) from file: ") + filename;
    QVERIFY2(tuneCount == count, message.toUtf8());
}

void MusicModelTest::loadModel(const QString &filename)
{
    try {
        m_model->load(filename);
    } catch (LP::Error &error) {
        qWarning() << "Error: " << QString::fromUtf8(error.what()) + filename;
    }
}

void MusicModelTest::testInvalidTunes()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_tune*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForSymbolCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::testValidTuneThreeValidSymbols()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_tune_three*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForSymbolCount(file.absoluteFilePath(), 3);
    }
}

void MusicModelTest::testLoadedInstrument()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_tune_test_loaded_instrument*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        loadModel(file.absoluteFilePath());

        QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
        QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);

        QVERIFY2(scoreIndex.isValid() && tuneIndex.isValid(), "No valid indexes");

        QVariant instrumentVar = tuneIndex.data(LP::TuneInstrument);
        QVERIFY2(instrumentVar.isValid(), "No valid instrument");
        QVERIFY2(instrumentVar.canConvert<InstrumentPtr>(), "Can't convert into instrument");

        InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
        QVERIFY2(instrument->name() == m_instrumentNames.at(0), "Valid instrument wasn't loaded");
    }
}

void MusicModelTest::testLoadedSymbolName()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_symbol_*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        loadModel(file.absoluteFilePath());

        QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
        QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);
        QModelIndex partIndex = m_model->index(0, 0, tuneIndex);
        QModelIndex measureIndex = m_model->index(0, 0, partIndex);
        QModelIndex symbolIndex = m_model->index(0, 0, measureIndex);

        QVERIFY2(scoreIndex.isValid() &&
                 tuneIndex.isValid() &&
                 partIndex.isValid() &&
                 measureIndex.isValid() &&
                 symbolIndex.isValid(), "No valid indexes");

        QVariant symbolNameVar = symbolIndex.data(LP::SymbolName);
        QVERIFY2(symbolNameVar.isValid(), "No valid symbol name");
        QVERIFY2(!symbolNameVar.toString().isEmpty(), "Symbol name is empty or invalid");

        QString symbolName = symbolNameVar.toString();
        QVERIFY2(symbolName == m_symbolNames.at(0), "Symbol name doesn't match");
    }
}

void MusicModelTest::testLoadedSymbolPitch()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "valid_symbolpitch*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        loadModel(file.absoluteFilePath());

        QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
        QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);
        QModelIndex partIndex = m_model->index(0, 0, tuneIndex);
        QModelIndex measureIndex = m_model->index(0, 0, partIndex);
        QModelIndex symbolIndex = m_model->index(0, 0, measureIndex);

        QVERIFY2(scoreIndex.isValid() &&
                 tuneIndex.isValid() &&
                 partIndex.isValid() &&
                 measureIndex.isValid() &&
                 symbolIndex.isValid(), "No valid indexes");

        QVariant symbolPitchVar = symbolIndex.data(LP::SymbolPitch);
        Q_ASSERT(symbolPitchVar.isValid());
        Q_ASSERT(symbolPitchVar.canConvert<PitchPtr>());

        PitchPtr pitch = symbolPitchVar.value<PitchPtr>();

        QVERIFY2(pitch->name() == "Low A", "Failed loading Pitch");
    }
}

void MusicModelTest::testSupportedDragAndDropActions()
{
    QVERIFY2(m_model->supportedDragActions() == Qt::MoveAction, "Model doesn't support move drag action");
    QVERIFY2(m_model->supportedDropActions() == Qt::MoveAction, "Model doesn't support move drop action");
}

void MusicModelTest::testMimeTypes()
{
    QVERIFY2(m_model->mimeTypes().contains(ScoreMimeType), "Mime types doesn't contain score type");
    QVERIFY2(m_model->mimeTypes().contains(TuneMimeType), "Mime types doesn't contain tune type");
    QVERIFY2(m_model->mimeTypes().contains(SymbolMimeType), "Mime types doesn't contain symbol type");
}

void MusicModelTest::testMimeData()
{
    populateModelWithTestdata();
    QModelIndex scoreIndex1 = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(scoreIndex1.isValid());
    QModelIndex scoreIndex2 = m_model->index(1, 0, QModelIndex());
    Q_ASSERT(scoreIndex2.isValid());

    QModelIndex tuneIndex1 = m_model->index(0, 0, scoreIndex1);
    Q_ASSERT(tuneIndex1.isValid());
    QModelIndex tuneIndex2 = m_model->index(0, 0, scoreIndex2);
    Q_ASSERT(tuneIndex2.isValid());

    QModelIndex partIndex1 = m_model->index(0, 0, tuneIndex1);
    Q_ASSERT(partIndex1.isValid());
    QModelIndex partIndex2 = m_model->index(0, 0, tuneIndex2);
    Q_ASSERT(partIndex2.isValid());

    QModelIndex measureIndex1 = m_model->index(0, 0, partIndex1);
    Q_ASSERT(measureIndex1.isValid());
    QModelIndex measureIndex2 = m_model->index(0, 0, partIndex2);
    Q_ASSERT(measureIndex2.isValid());

    QModelIndex symbolIndex1 = m_model->index(0, 0, measureIndex1);
    Q_ASSERT(symbolIndex1.isValid());
    QModelIndex symbolIndex2 = m_model->index(1, 0, measureIndex1);
    Q_ASSERT(symbolIndex2.isValid());

    QModelIndexList indexList = QModelIndexList() << tuneIndex1 << scoreIndex1;
    QVERIFY2(m_model->mimeData(indexList) == 0, "Model should always return 0 if model indexes are from different hierarchy");

    indexList.clear();
    indexList << symbolIndex1 << symbolIndex2;
    QVERIFY2(m_model->mimeData(indexList) != 0, "Model should return non 0 value if indexes are the same hierarchy");

    indexList.clear();
    indexList << scoreIndex1 << scoreIndex2;
    checkMimeDataForTags(indexList, "SCORE");

    indexList.clear();
    indexList << tuneIndex1 << tuneIndex2;
    checkMimeDataForTags(indexList, "TUNE");

    indexList.clear();
    indexList << partIndex1 << partIndex2;
    checkMimeDataForTags(indexList, "PART");

    indexList.clear();
    indexList << measureIndex1 << measureIndex2;
    checkMimeDataForTags(indexList, "MEASURE");

    indexList.clear();
    indexList << symbolIndex1 << symbolIndex2;
    checkMimeDataForTags(indexList, "SYMBOL");
}

void MusicModelTest::testDropMimeDataScores()
{
    populateModelWithTestdata();
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(scoreIndex.isValid());
    QModelIndex scoreIndex2 = m_model->index(1, 0, QModelIndex());
    Q_ASSERT(scoreIndex2.isValid());
    QMimeData *data = m_model->mimeData(QModelIndexList() << scoreIndex << scoreIndex2);

    QString scoreTitleRow0 = m_model->data(scoreIndex, LP::ScoreTitle).toString();
    Q_ASSERT(!scoreTitleRow0.isEmpty());
    QString scoreTitleRow1 = m_model->data(scoreIndex2, LP::ScoreTitle).toString();
    Q_ASSERT(!scoreTitleRow1.isEmpty());

    MusicModel model2;
    model2.dropMimeData(data, Qt::MoveAction, 0, 0, QModelIndex());
    QVERIFY2(model2.rowCount(QModelIndex()) == 2, "Failed dropping scores into model");

    QModelIndex droppedScore1 = model2.index(0, 0, QModelIndex());
    QString droppedScoreTitleRow0 = model2.data(droppedScore1, LP::ScoreTitle).toString();
    Q_ASSERT(!droppedScoreTitleRow0.isEmpty());

    QModelIndex droppedScore2 = model2.index(1, 0, QModelIndex());
    QString droppedScoreTitleRow1 = model2.data(droppedScore2, LP::ScoreTitle).toString();
    Q_ASSERT(!droppedScoreTitleRow1.isEmpty());

    QVERIFY2(scoreTitleRow0 == droppedScoreTitleRow0, "Dropped score in row 0 is on wrong place");
    QVERIFY2(scoreTitleRow1 == droppedScoreTitleRow1, "Dropped score in row 1 is on wrong place");

    model2.clear();
    model2.dropMimeData(data, Qt::MoveAction, -1, -1, QModelIndex());
    QVERIFY2(model2.rowCount(QModelIndex()) == 2, "Failed dropping scores at end");
}

void MusicModelTest::testDropMimeDataTunes()
{
    populateModelWithTestdata();
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(scoreIndex.isValid());
    QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);
    Q_ASSERT(tuneIndex.isValid());
    QMimeData *data = m_model->mimeData(QModelIndexList() << tuneIndex);

    MusicModel model2;
    QModelIndex scoreModel2 = model2.insertScore(0, "New Score");
    model2.dropMimeData(data, Qt::MoveAction, 0, 0, scoreModel2);
    QVERIFY2(model2.rowCount(scoreModel2) == 1, "Tune wasn't inserted");

    model2.clear();
    scoreModel2 = model2.insertScore(0, "New Score");
    model2.dropMimeData(data, Qt::MoveAction, -1, 0, scoreModel2);
    QVERIFY2(model2.rowCount(scoreModel2) == 1, "Failed dropping tune at end");
}

void MusicModelTest::testDropMimeDataParts()
{
    populateModelWithTestdata();
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(scoreIndex.isValid());
    QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);
    Q_ASSERT(tuneIndex.isValid());
    QModelIndex partIndex = m_model->index(0, 0, tuneIndex);
    QMimeData *data = m_model->mimeData(QModelIndexList() << partIndex);

    MusicModel model2;
    QModelIndex tuneIndex2 = model2.insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    model2.dropMimeData(data, Qt::MoveAction, 0, 0, tuneIndex2);
    QVERIFY2(model2.rowCount(tuneIndex2) == 1, "Part wasn't inserted");

    model2.clear();
    tuneIndex2 = model2.insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    model2.dropMimeData(data, Qt::MoveAction, -1, 0, tuneIndex2);
    QVERIFY2(model2.rowCount(tuneIndex2) == 1, "Failed dropping part at end");
}

void MusicModelTest::testDropMimeDataMeasures()
{
    populateModelWithTestdata();
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(scoreIndex.isValid());
    QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);
    Q_ASSERT(tuneIndex.isValid());
    QModelIndex partIndex = m_model->index(0, 0, tuneIndex);
    Q_ASSERT(partIndex.isValid());
    QModelIndex measureIndex = m_model->index(0, 0, partIndex);
    Q_ASSERT(measureIndex.isValid());
    QMimeData *data = m_model->mimeData(QModelIndexList() << measureIndex);

    int measureCountBeforeDrop = 8;
    MusicModel model2;
    QModelIndex tuneIndex2 = model2.insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex partIndex2 = model2.insertPartIntoTune(0, tuneIndex2, measureCountBeforeDrop, true);
    model2.dropMimeData(data, Qt::MoveAction, 0, 0, partIndex2);
    QVERIFY2(model2.rowCount(partIndex2) == measureCountBeforeDrop + 1, "Measure wasn't inserted");

    model2.clear();
    tuneIndex2 = model2.insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    partIndex2 = model2.insertPartIntoTune(0, tuneIndex2, measureCountBeforeDrop, true);
    model2.dropMimeData(data, Qt::MoveAction, -1, 0, partIndex2);
    QVERIFY2(model2.rowCount(partIndex2) == measureCountBeforeDrop + 1, "Failed dropping measure at end");
}

void MusicModelTest::testDropMimeDataSymbols()
{
    QString symbolNameWithLength = "Testsymbol with pitch and length";
    populateModelWithTestdata();
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(scoreIndex.isValid());
    QModelIndex tuneIndex = m_model->index(0, 0, scoreIndex);
    Q_ASSERT(tuneIndex.isValid());
    QModelIndex partIndex = m_model->index(0, 0, tuneIndex);
    Q_ASSERT(partIndex.isValid());
    QModelIndex measureIndex = m_model->index(0, 0, partIndex);
    Q_ASSERT(measureIndex.isValid());

    for (int i = 0; i < 2; i++)
        m_model->insertSymbolIntoMeasure(0, measureIndex, symbolNameWithLength);

    QModelIndex symbol1 = m_model->index(0, 0, measureIndex);
    m_model->setData(symbol1, QVariant::fromValue<Length::Value>(Length::_1), LP::SymbolLength);
    QModelIndex symbol2 = m_model->index(1, 0, measureIndex);
    m_model->setData(symbol2, QVariant::fromValue<Length::Value>(Length::_2), LP::SymbolLength);

    Q_ASSERT(m_model->data(symbol1, LP::SymbolLength).isValid());

    QMimeData *data = m_model->mimeData(QModelIndexList() << symbol1 << symbol2);
    MusicModel model2;
    QModelIndex tuneModel2 = model2.insertTuneWithScore(0, "test score", m_instrumentNames.at(0));
    QModelIndex partIndex2 = m_model->insertPartIntoTune(0, tuneModel2, 10);
    QModelIndex measureIndex2 = m_model->index(0, 0, partIndex2);
    Q_ASSERT(measureIndex2.isValid());

    model2.dropMimeData(data, Qt::MoveAction, 0, 0, measureIndex2);

    int symbolCount = model2.rowCount(measureIndex2);
    QVERIFY2(symbolCount == 2, "Failed inserting symbols");
    QModelIndex model2Symbol = model2.index(0, 0, measureIndex2);
    QVERIFY2(model2.data(model2Symbol, LP::SymbolLength).canConvert<Length::Value>(), "Failed getting data from inserted symbol");
    QVERIFY2(model2.data(model2Symbol, LP::SymbolLength).value<Length::Value>() == Length::_1, "Symbol was inserted in wrong place");

    model2.clear();

    tuneModel2 = model2.insertTuneWithScore(0, "test score", m_instrumentNames.at(0));
    partIndex2 = m_model->insertPartIntoTune(0, tuneModel2, 10);
    measureIndex2 = m_model->index(0, 0, partIndex2);
    model2.dropMimeData(data, Qt::MoveAction, -1, 0, measureIndex2);

    QVERIFY2(model2.rowCount(measureIndex2) == 2, "Failed inserting symbols at end");
}

void MusicModelTest::testUndoStackInsertScore()
{
    m_model->insertScore(0, "First Score");
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    QVERIFY2(m_model->undoStack()->count() == 1, "No command/too many commands pushed on undo stack");
    QVERIFY2(m_model->rowCount(QModelIndex()) == 1, "No score was inserted into model");
    QVERIFY2(m_model->rowCount(scoreIndex) == 0, "Score has child elements");

    m_model->undoStack()->undo();
    QVERIFY2(m_model->rowCount(QModelIndex()) == 0, "Score wasn't removed after undo");

    m_model->undoStack()->redo();
    scoreIndex = m_model->index(0, 0, QModelIndex());
    QVERIFY2(m_model->data(scoreIndex, LP::ScoreTitle).toString() == "First Score", "Redo doesn't insert the same score");
}

void MusicModelTest::testUndoStackAppendScore()
{
    m_model->appendScore("First Score");
    QVERIFY2(m_model->undoStack()->count() == 1, "No command/too many commands pushed on undo stack");
    QVERIFY2(m_model->rowCount(QModelIndex()) == 1, "No score was inserted into model");

    m_model->undoStack()->undo();
    QVERIFY2(m_model->rowCount(QModelIndex()) == 0, "Score wasn't removed after undo");
}

void MusicModelTest::testUndoStackInsertTuneIntoScore()
{
    QModelIndex score = m_model->insertScore(0, "First score");
    Q_ASSERT(m_model->undoStack()->count() == 1);
    m_model->insertTuneIntoScore(0, score, m_instrumentNames.at(0));

    QVERIFY2(m_model->undoStack()->count() == 2, "No command/too many commands pushed on undo stack");
    QVERIFY2(m_model->rowCount(score) == 1, "No tune was inserted into score");

    m_model->undoStack()->undo();
    QVERIFY2(m_model->rowCount(score) == 0, "Tune wasn't removed after undo");
}

void MusicModelTest::testUndoStackAppendTuneToScore()
{
    QModelIndex score = m_model->insertScore(0, "First score");
    Q_ASSERT(m_model->undoStack()->count() == 1);
    m_model->appendTuneToScore(score, m_instrumentNames.at(0));

    QVERIFY2(m_model->undoStack()->count() == 2, "No command/too many commands pushed on undo stack");
    QVERIFY2(m_model->rowCount(score) == 1, "No tune was inserted into score");

    m_model->undoStack()->undo();
    QVERIFY2(m_model->rowCount(score) == 0, "Tune wasn't removed after undo");
}

void MusicModelTest::testUndoStackInsertTuneWithScore()
{
    m_model->insertTuneWithScore(0, "First score", m_instrumentNames.at(0));
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    QVERIFY2(m_model->undoStack()->count() == 1, "No command/too many commands pushed on undo stack");
    QVERIFY2(m_model->rowCount(QModelIndex()) == 1, "No score was inserted into model");
    QVERIFY2(m_model->rowCount(scoreIndex) == 1, "Score has no child elements");

    m_model->undoStack()->undo();
    QVERIFY2(m_model->rowCount(QModelIndex()) == 0, "Score with tune wasn't removed after undo");

    m_model->undoStack()->redo();
    QVERIFY2(m_model->rowCount(QModelIndex()) == 1, "No score was inserted into model after redo");
    QVERIFY2(m_model->rowCount(scoreIndex) == 1, "Score has no child elements after redo");
}

void MusicModelTest::testUndoStackInsertPart()
{
    QModelIndex tuneIndex = m_model->insertTuneWithScore(0, "First score", m_instrumentNames.at(0));
    m_model->insertPartIntoTune(0, tuneIndex, 9);
    QVERIFY2(m_model->undoStack()->count() == 2, "No command/too many commands pushed on undo stack");
}

void MusicModelTest::testUndoStackInsertSymbol()
{
    int measureCount = 10;
    QModelIndex tune = m_model->insertTuneWithScore(0, "First score", m_instrumentNames.at(0));
    QModelIndex part = m_model->insertPartIntoTune(0, tune, measureCount);
    QModelIndex measure = m_model->index(0, 0, part);

    Q_ASSERT(m_model->undoStack()->count() == 2);
    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));
    QVERIFY2(m_model->rowCount(measure) == 1 , "No symbol was inserted into model");
    QVERIFY2(m_model->undoStack()->count() == 3, "No command/too many commands pushed on undo stack");

    m_model->undoStack()->undo();
    QVERIFY2(m_model->rowCount(measure) == 0, "Symbol wasn't removed after undo");

    m_model->undoStack()->redo();
    QVERIFY2(m_model->rowCount(measure) == 1, "No symbol was inserted into model after redo");
}

void MusicModelTest::testUndoStackRemoveRows()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First score", m_instrumentNames.at(0));
    QModelIndex part = m_model->insertPartIntoTune(0, tune, 5);
    QModelIndex measure = m_model->index(0, 0, part);

    Q_ASSERT(m_model->undoStack()->count() == 2);
    for (int i = 0; i < 5; i++) {
        m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));
    }

    int undoStackCountBefore = m_model->undoStack()->count();
    MusicItem *item0 = m_model->itemForIndex(m_model->index(0, 0, measure));
    MusicItem *item1 = m_model->itemForIndex(m_model->index(1, 0, measure));
    MusicItem *item2 = m_model->itemForIndex(m_model->index(2, 0, measure));
    MusicItem *item3 = m_model->itemForIndex(m_model->index(3, 0, measure));
    MusicItem *item4 = m_model->itemForIndex(m_model->index(4, 0, measure));


    m_model->removeRows(1, 3, measure);
    QVERIFY2(m_model->undoStack()->count() - 1 == undoStackCountBefore, "No command/too many commands pushed on undo stack");
    QVERIFY2(m_model->rowCount(measure) == 2, "Failed removing rows");
    QVERIFY2(m_model->itemForIndex(m_model->index(1, 0, measure)) == item4, "last item is on the wrong place");

    m_model->undoStack()->undo();
    QVERIFY2(m_model->rowCount(measure) == 5, "Failed undo removing of items");
    QVERIFY2(item0 == m_model->itemForIndex(m_model->index(0, 0, measure)), "item on wrong place after undo");
    QVERIFY2(item1 == m_model->itemForIndex(m_model->index(1, 0, measure)), "item on wrong place after undo");
    QVERIFY2(item2 == m_model->itemForIndex(m_model->index(2, 0, measure)), "item on wrong place after undo");
    QVERIFY2(item3 == m_model->itemForIndex(m_model->index(3, 0, measure)), "item on wrong place after undo");
    QVERIFY2(item4 == m_model->itemForIndex(m_model->index(4, 0, measure)), "item on wrong place after undo");

    m_model->undoStack()->redo();
    QVERIFY2(m_model->undoStack()->count() - 1 == undoStackCountBefore, "No command/too many commands pushed on undo stack");
    QVERIFY2(m_model->rowCount(measure) == 2, "Failed removing rows");
    QVERIFY2(m_model->itemForIndex(m_model->index(1, 0, measure)) == item4, "last item is on the wrong place");
}

void MusicModelTest::testUndoStackDropMimeData()
{
    populateModelWithTestdata();
    QModelIndex scoreIndex = m_model->index(0, 0, QModelIndex());
    Q_ASSERT(scoreIndex.isValid());
    QModelIndex scoreIndex2 = m_model->index(1, 0, QModelIndex());
    Q_ASSERT(scoreIndex2.isValid());
    QMimeData *data = m_model->mimeData(QModelIndexList() << scoreIndex << scoreIndex2);

    MusicModel model2;
    model2.dropMimeData(data, Qt::MoveAction, 0, 0, QModelIndex());

    QVERIFY2(model2.undoStack()->count() == 1, "No command/too many commands pushed on undo stack while inserting");

    MusicModel model3;
    model3.dropMimeData(data, Qt::MoveAction, -1, 0, QModelIndex());
    QVERIFY2(model2.undoStack()->count() == 1, "No command/too many commands pushed on undo stack while appending");
}

void MusicModelTest::populateModelWithTestdata()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", m_instrumentNames.at(0));
    QModelIndex part = m_model->appendPartToTune(tune, 8, true);
    QModelIndex measure = m_model->index(0, 0, part);

    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));
    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(1));

    tune = m_model->insertTuneWithScore(0, "Second Score", m_instrumentNames.at(0));
    part = m_model->appendPartToTune(tune, 8, true);
    measure = m_model->index(0, 0, part);

    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(1));
    m_model->insertSymbolIntoMeasure(0, measure, m_symbolNames.at(0));
}

void MusicModelTest::checkMimeDataForTags(const QModelIndexList &indexes, const QString &tagName)
{
    QMimeData *mimeData = m_model->mimeData(indexes);
    checkMimeDataForTagname(mimeData, tagName);

    QVERIFY2(mimeData->formats().count(), "No mime date format is supported by data");
    QVERIFY2(mimeData->formats().count() == 1, "More than one format is supported by data");
    const QString dataFormat = mimeData->formats().at(0);

    QByteArray xmlData = qUncompress(mimeData->data(dataFormat));
    Q_ASSERT(!xmlData.isEmpty());

    QXmlStreamReader reader(xmlData);
    checkRootChildItemsForTagnameAndCount(&reader, tagName, indexes.count());
}

void MusicModelTest::checkMimeDataForTagname(const QMimeData *data, const QString &tagname)
{
    if (tagname.compare("SCORE", Qt::CaseInsensitive) == 0) {
        QVERIFY2(data->hasFormat(ScoreMimeType), "Mime data has no score format");
        return;
    }
    else if (tagname.compare("TUNE", Qt::CaseInsensitive) == 0) {
        QVERIFY2(data->hasFormat(TuneMimeType), "Mime data has no tune format");
        return;
    }
    else if (tagname.compare("SYMBOL", Qt::CaseInsensitive) == 0) {
        QVERIFY2(data->hasFormat(SymbolMimeType), "Mime data has no symbol format");
        return;
    }
    else {
        Q_ASSERT(true);
    }
}

void MusicModelTest::checkRootChildItemsForTagnameAndCount(QXmlStreamReader *reader, const QString &tagName, int count)
{
    QStack<QString> tagNameStack;

    int countOfXmlRootChildTags = 0;
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            if (tagNameStack.count() == 1) { // Root child
                if (tagName.compare(reader->name(), Qt::CaseInsensitive) == 0) {
                    countOfXmlRootChildTags++;
                } else {
                    Q_ASSERT(true);
                }
            }
            tagNameStack.push(QString().append(reader->name()));
        }
        if (reader->isEndElement()) {
            bool tagNameIsTopOfStack = tagNameStack.top().compare(reader->name(), Qt::CaseInsensitive) == 0;

            QVERIFY2(tagNameIsTopOfStack, "No valid xml");
            Q_ASSERT(tagNameIsTopOfStack);

            if (tagNameIsTopOfStack) {
                tagNameStack.pop();
            }
        }
    }

    QString errorMessage = reader->errorString();
    QVERIFY2(!reader->hasError(), errorMessage.toUtf8());

    QVERIFY2(count == countOfXmlRootChildTags, "Wrong count of root items in mime data");
}

void MusicModelTest::testInvalidSymbols()
{
    QFileInfoList fileInfos = fileInfosForPatternList(QStringList() << "invalid_symbol*.lime");
    Q_ASSERT(fileInfos.count() > 0);

    foreach (QFileInfo file, fileInfos) {
        checkForSymbolCount(file.absoluteFilePath(), 0);
    }
}

void MusicModelTest::checkForSymbolCount(const QString &filename, int count)
{
    loadModel(filename);
    QModelIndex scoreIndex =    m_model->index(0, 0, QModelIndex());
    QModelIndex tuneIndex =     m_model->index(0, 0, scoreIndex);
    QModelIndex partIndex =     m_model->index(0, 0, tuneIndex);
    QModelIndex measureIndex =  m_model->index(0, 0, partIndex);

    int symbolCount = 0;
    QString message = QString("No valid Index for score in file: ") + filename;
    QVERIFY2(scoreIndex.isValid(), message.toUtf8());

    message = QString("No valid Index for tune in file: ") + filename;
    QVERIFY2(tuneIndex.isValid(), message.toUtf8());

    message = QString("No valid Index for part in file: ") + filename;
    QVERIFY2(partIndex.isValid(), message.toUtf8());

    message = QString("No valid Index for measure in file: ") + filename;
    QVERIFY2(measureIndex.isValid(), message.toUtf8());
    symbolCount = m_model->rowCount(measureIndex);

    message = QString("Wrong count of symbols loaded (" + QString::number(symbolCount) + " symbols) from file: ") + filename;
    QVERIFY2(symbolCount == count, message.toUtf8());
}

QTEST_MAIN(MusicModelTest)
