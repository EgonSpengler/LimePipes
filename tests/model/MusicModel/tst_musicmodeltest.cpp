/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "qt_modeltest/modeltest.h"
#include <musicmodel.h>
#include <itemdatatypes.h>
#include <instrument.h>
#include <symbol.h>

class MusicModelTest : public QObject
{
    Q_OBJECT
    
public:
    MusicModelTest();

public slots:
    void rowsInsertedAssertFail() {
        // This slot will be connected with the rowsInserted Signal of the model
        // to check that items weren't inserted
        QVERIFY2(false, "Rows were inserted");
    }
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testInsertScore();
    void testAppendScore();
    void testInsertTuneIntoScore();
    void testAppendTuneToScore();
    void testInsertTuneWithScore();
    void testInsertSymbol();
    void testQAbstractItemModelImplementation();
    void testItemForIndex();
    void testClear();

private:
    MusicModel *m_model;
};

MusicModelTest::MusicModelTest()
    : m_model(0)
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

void MusicModelTest::testInsertScore()
{
    QModelIndex firstScore = m_model->insertScore(0, "First Title");
    QVERIFY2(m_model->rowCount(QModelIndex()) == 1, "Score was not inserted");
    QVERIFY2(firstScore.isValid(), "No valid Modelindex was returned while inserting score");
    QVERIFY2(firstScore.row() == 0, "Score was inserted in wrong row");
    QVERIFY2(firstScore.column() == 0, "Score was inserted in wrong column");
    QVERIFY2(m_model->data(firstScore, LP::scoreTitle) == "First Title", "Failed score title");

    m_model->setData(firstScore, "Score 1", LP::scoreTitle);
    QModelIndex secondScore = m_model->insertScore(m_model->rowCount(QModelIndex()), "Second Title");
    m_model->setData(secondScore, "Score 2", LP::scoreTitle);
    QVERIFY2(secondScore.data(LP::scoreTitle) == "Score 2", "Score 2's title isn't there");
    QVERIFY2(secondScore.row() == m_model->rowCount(QModelIndex()) - 1, "Score 2 was inserted in wrong row");
    QVERIFY2(secondScore.column() == 0, "Score 2 was inserted in wrong column");

    // Now, the rowsInserted signal should not be called when inserting rows
    QObject::connect(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)),
                     this, SLOT(rowsInsertedAssertFail()));
    m_model->insertScore(-1, "Failed Score1");
    m_model->insertScore(5, "Failed Score2");
}

void MusicModelTest::testAppendScore()
{
    QModelIndex firstScore = m_model->appendScore("First title");
    QVERIFY2(firstScore.isValid(), "Failed appending score");
    QVERIFY2(m_model->data(firstScore, LP::scoreTitle) == "First title", "Failed getting title from appended score");
}

void MusicModelTest::testInsertTuneIntoScore()
{
    QModelIndex score = m_model->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_model->insertTuneIntoScore(0, score, new Instrument(LP::BassDrum, "Bass drum"));
    Instrument *instrument = m_model->data(tune, LP::tuneInstrument).value<Instrument *>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == "Bass drum", "Failed getting instrument back");

    // Now, the rowsInserted signal should not be called when inserting rows
    QObject::connect(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)),
                     this, SLOT(rowsInsertedAssertFail()));
    Instrument *instrument2 = new Instrument(LP::BassDrum, "Bass drum2");
    m_model->insertTuneIntoScore(-1, score, instrument2);
    m_model->insertTuneIntoScore(5, score, instrument2);
}

void MusicModelTest::testAppendTuneToScore()
{
    QModelIndex score = m_model->insertScore(0, "First Score");
    QVERIFY2(score.isValid(), "Failed inserting score");
    QModelIndex tune = m_model->appendTuneToScore(score, new Instrument(LP::BassDrum, "Bass drum"));
    Instrument *instrument = m_model->data(tune, LP::tuneInstrument).value<Instrument *>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == "Bass drum", "Failed getting instrument back");
}

void MusicModelTest::testInsertTuneWithScore()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", new Instrument(LP::BassDrum, "Bass drum"));
    Instrument *instrument = m_model->data(tune, LP::tuneInstrument).value<Instrument *>();

    QVERIFY2(tune.isValid(), "Failed inserting Tune");
    QVERIFY2(instrument->name() == "Bass drum", "Failed getting score title from index");
    // New tune and new score => tune in row and column 0
    QVERIFY2(tune.column() == 0, "Tune is in wrong column");
    QVERIFY2(tune.row() == 0, "Tune is in wrong row");
}

void MusicModelTest::testInsertSymbol()
{
    QModelIndex tune = m_model->insertTuneWithScore(0, "First Score", new Instrument(LP::BassDrum, "Bass drum"));
    QModelIndex symbol1 = m_model->insertSymbol(0, tune, new Symbol(LP::Bar, "testsymbol"));
    QVERIFY2(symbol1.isValid(), "Failed inserting symbol");
    QVERIFY2(m_model->data(symbol1, LP::symbolName) == "testsymbol", "Failed getting symbol's name");

    // Now, the rowsInserted signal should not be called when inserting rows
    QObject::connect(m_model, SIGNAL(rowsInserted(const QModelIndex, int, int)),
                     this, SLOT(rowsInsertedAssertFail()));
    Symbol *symbol2 = new Symbol(LP::Bar, "testsymbol2");
    m_model->insertSymbol(5, tune, symbol2);
    m_model->insertSymbol(-1, tune, symbol2);
    delete symbol2;
}


void MusicModelTest::testQAbstractItemModelImplementation()
{
    Instrument *instrument = new Instrument(LP::GreatHighlandBagpipe, "Bagpipe");
    for (int i=0; i < 3; i++) {
        m_model->insertScore(0, "Score Title");
    }

    QModelIndex secondScore = m_model->index(1, 0, QModelIndex());
    QVERIFY2(secondScore.isValid(), "Failed getting valid score");

    QModelIndex tune1 = m_model->insertTuneIntoScore(0, secondScore, instrument);
    m_model->insertTuneIntoScore(0, secondScore, instrument);

    m_model->insertSymbol(0, tune1, new Symbol(LP::Bar, "Bar"));
    m_model->insertSymbol(1, tune1, new Symbol(LP::Bar, "Bar"));
    m_model->insertSymbol(2, tune1, new Symbol(LP::Bar, "Bar"));
    m_model->insertSymbol(1, tune1, new Symbol(LP::MelodyNote, "Melody note"));

    ModelTest * modelTest = new ModelTest(m_model, this);
    delete modelTest;
}

void MusicModelTest::testItemForIndex()
{
    QModelIndex scoreIndex = m_model->insertScore(0, "Random Title");
    MusicItem *score = m_model->itemForIndex(scoreIndex);
    QVERIFY2(score->data(LP::scoreTitle) == "Random Title", "Failed to get the correct item for an index");
}

void MusicModelTest::testClear()
{
    m_model->insertScore(0, "Title");
    QVERIFY2(m_model->index(0, 0, QModelIndex()).isValid() == true, "At least one item should be in the model for next test");
    m_model->clear();
    QVERIFY2(m_model->index(0, 0, QModelIndex()).isValid() == false, "Model wasn't cleared");
}

QTEST_APPLESS_MAIN(MusicModelTest)

#include "tst_musicmodeltest.moc"
