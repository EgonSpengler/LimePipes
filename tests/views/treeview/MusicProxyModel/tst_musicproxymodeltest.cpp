/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QMetaType>
#include <musicmodel.h>
#include <itemdatatypes.h>
#include <instrument.h>
#include <symbol.h>
#include <score.h>
#include <tune.h>
#include <musicproxymodel.h>

namespace {

class SymbolWithPitchAndLength : public Symbol
{
public:
    SymbolWithPitchAndLength()
        : Symbol()
    {
        setSymbolOptions(Symbol::HasPitch |
                         Symbol::HasLength);
        initData(QVariant::fromValue<PitchPtr>(PitchPtr(new Pitch(2, "testpitch"))), LP::symbolPitch);
        initData(QVariant::fromValue<Length::Value>(Length::_32), LP::symbolLength);
    }
};

class TestInstrument : public Instrument
{
public:
    static int notOkToInsertSymbolType;
    TestInstrument()
        : Instrument(LP::BassDrum, "Bass drum") {}
    bool supportsSymbolType(int type) const {
        if (type == notOkToInsertSymbolType) {
            return false;
        }
        return true;
    }
};
int TestInstrument::notOkToInsertSymbolType = 123456;
}

class MusicProxyModelTest : public QObject
{
    Q_OBJECT
    
public:
    MusicProxyModelTest()
        : m_sourceModel(0),
          m_proxyModel(0)
    { qRegisterMetaType<QModelIndex>("QModelIndex"); }
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testColumnCount();
    void testInsertScore();
    void testAppendScore();
    void testInsertTuneIntoScore();
    void testAppendTuneToScore();
    void testInsertTuneWithScore();
    void testInsertSymbol();
    void testCallOfOkToInsertChild();
    void testItemForIndex();
    void testClear();
    void testIsScore();
    void testIsTune();
    void testIsSymbol();
    void testScoreFromIndex();
    void testTuneFromIndex();
    void testSymbolFromIndex();
    void testPitchColumn();
    void testLengthColumn();

private:
    MusicModel *m_sourceModel;
    MusicProxyModel *m_proxyModel;
};

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
    QVERIFY2(m_proxyModel->data(firstScore, LP::scoreTitle) == "First Title", "Failed score title");

    m_proxyModel->setData(firstScore, "Score 1", LP::scoreTitle);
    QModelIndex secondScore = m_proxyModel->insertScore(m_proxyModel->rowCount(QModelIndex()), "Second Title");
    m_proxyModel->setData(secondScore, "Score 2", LP::scoreTitle);
    QVERIFY2(secondScore.data(LP::scoreTitle) == "Score 2", "Score 2's title isn't there");
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
    QVERIFY2(m_proxyModel->data(firstScore, LP::scoreTitle) == "First title", "Failed getting title from appended score");
}

void MusicProxyModelTest::testInsertTuneIntoScore()
{
    QModelIndex score = m_proxyModel->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_proxyModel->insertTuneIntoScore(0, score, InstrumentPtr(new TestInstrument()));
    InstrumentPtr instrument = m_proxyModel->data(tune, LP::tuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == "Bass drum", "Failed getting instrument back");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_proxyModel, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    InstrumentPtr instrument2 = InstrumentPtr(new TestInstrument());
    m_proxyModel->insertTuneIntoScore(-1, score, instrument2);
    m_proxyModel->insertTuneIntoScore(5, score, instrument2);

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicProxyModelTest::testAppendTuneToScore()
{
    QModelIndex score = m_proxyModel->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_proxyModel->appendTuneToScore(score, InstrumentPtr(new TestInstrument()));
    InstrumentPtr instrument = m_proxyModel->data(tune, LP::tuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == "Bass drum", "Failed getting instrument back");
}

void MusicProxyModelTest::testInsertTuneWithScore()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", InstrumentPtr(new TestInstrument()));
    InstrumentPtr instrument = m_proxyModel->data(tune, LP::tuneInstrument).value<InstrumentPtr>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == "Bass drum", "Failed getting score title from index");
    // New tune and new score => tune in row and column 0
    QVERIFY2(tune.column() == 0, "Tune is in wrong column");
    QVERIFY2(tune.row() == 0, "Tune is in wrong row");
}

void MusicProxyModelTest::testInsertSymbol()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", InstrumentPtr(new TestInstrument()));
    QModelIndex symbol1 = m_proxyModel->insertSymbol(0, tune, new Symbol(LP::Bar, "testsymbol"));
    QVERIFY2(symbol1.isValid(), "Failed inserting symbol");
    QVERIFY2(m_proxyModel->data(symbol1, LP::symbolName) == "testsymbol", "Failed getting symbol's name");

    // Now, the rowsInserted signal should not be called when inserting rows
    QSignalSpy spy(m_proxyModel, SIGNAL(rowsInserted(const QModelIndex, int, int)));

    Symbol *symbol2 = new Symbol(LP::Bar, "testsymbol2");
    m_proxyModel->insertSymbol(5, tune, symbol2);
    m_proxyModel->insertSymbol(-1, tune, symbol2);
    delete symbol2;

    QVERIFY2(spy.count() == 0, "rowsInserted Signal was emitted" );
}

void MusicProxyModelTest::testCallOfOkToInsertChild()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", InstrumentPtr(new TestInstrument()));

    QModelIndex validSymbol = m_proxyModel->insertSymbol(0, tune, new Symbol(LP::Bar, "valid symbol"));
    QVERIFY2(validSymbol.isValid(), "Failed inserting valid symbol");

    QModelIndex invalidSymbol = m_proxyModel->insertSymbol(0, tune, new Symbol(TestInstrument::notOkToInsertSymbolType, "invalid symbol"));
    QVERIFY2(invalidSymbol.isValid() == false, "Failed. It was possible to insert a invalid symbol");
}

void MusicProxyModelTest::testItemForIndex()
{
    QModelIndex scoreIndex = m_proxyModel->insertScore(0, "Random Title");
    MusicItem *score = m_proxyModel->itemForIndex(scoreIndex);
    QVERIFY2(score->data(LP::scoreTitle) == "Random Title", "Failed to get the correct item for an index");
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
    QModelIndex tune = m_proxyModel->appendTuneToScore(score, InstrumentPtr(new TestInstrument()));
    QVERIFY2(m_proxyModel->isIndexTune(tune), "Faile, should return true for tune");
}

void MusicProxyModelTest::testIsSymbol()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", InstrumentPtr(new TestInstrument()));
    QModelIndex symbol1 = m_proxyModel->insertSymbol(0, tune, new Symbol(LP::Bar, "testsymbol"));
    QVERIFY2(m_proxyModel->isIndexSymbol(symbol1), "Failed, should return true for symbol");
}

void MusicProxyModelTest::testScoreFromIndex()
{
    QModelIndex firstScore = m_proxyModel->appendScore("First title");
    QVERIFY2(m_proxyModel->scoreFromIndex(firstScore)->type() == MusicItem::ScoreType, "Failed getting score from index");
}

void MusicProxyModelTest::testTuneFromIndex()
{
    QModelIndex score = m_proxyModel->insertScore(0, "First Score");
    QModelIndex tune = m_proxyModel->appendTuneToScore(score, InstrumentPtr(new TestInstrument()));
    QVERIFY2(m_proxyModel->tuneFromIndex(tune)->type() == MusicItem::TuneType, "Failed getting tune from index");
}

void MusicProxyModelTest::testSymbolFromIndex()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", InstrumentPtr(new TestInstrument()));
    QModelIndex symbol1 = m_proxyModel->insertSymbol(0, tune, new Symbol(LP::Bar, "testsymbol"));
    QVERIFY2(m_proxyModel->symbolFromIndex(symbol1)->type() == MusicItem::SymbolType, "Failed getting symbol from index");
}

void MusicProxyModelTest::testPitchColumn()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", InstrumentPtr(new TestInstrument()));
    QModelIndex symbolWithPitch = m_proxyModel->insertSymbol(0, tune, new SymbolWithPitchAndLength());

    QModelIndex pitchIndex = m_proxyModel->sibling(symbolWithPitch.row(), MusicProxyModel::PitchColumn, symbolWithPitch);
    QVERIFY2(symbolWithPitch.isValid(), "Failed inserting symbol with pitch");
    QVERIFY2(pitchIndex.isValid(), "Fail, pitch index isn't valid");

    QVariant pitchVariant = m_proxyModel->data(pitchIndex, LP::symbolPitch);
    QVERIFY2(pitchVariant.canConvert<PitchPtr>(), "Pitch wasn't returned");
    QVERIFY2(pitchVariant.value<PitchPtr>()->name() == "testpitch", "Wrong pitch was returned");
}

void MusicProxyModelTest::testLengthColumn()
{
    QModelIndex tune = m_proxyModel->insertTuneWithScore(0, "First Score", InstrumentPtr(new TestInstrument()));
    QModelIndex symbolWithLength = m_proxyModel->insertSymbol(0, tune, new SymbolWithPitchAndLength());

    QModelIndex lengthIndex = m_proxyModel->sibling(symbolWithLength.row(), MusicProxyModel::LengthColumn, symbolWithLength);
    QVERIFY2(symbolWithLength.isValid(), "Failed inserting symbol with length");
    QVERIFY2(lengthIndex.isValid(), "Fail, length index isn't valid");
}

QTEST_APPLESS_MAIN(MusicProxyModelTest)

#include "tst_musicproxymodeltest.moc"
