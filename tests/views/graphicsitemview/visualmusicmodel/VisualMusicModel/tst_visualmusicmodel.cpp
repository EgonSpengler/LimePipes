/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QCoreApplication>
#include <QStandardItemModel>
#include <model/musicmodel.h>
#include <graphicsitemview/visualmusicmodel/visualscore.h>
#include <views/graphicsitemview/visualmusicmodel/visualmusicmodel.h>
#include "tst_visualmusicmodel.h"

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

VisualMusicModelTest::VisualMusicModelTest(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<QModelIndex>("QModelIndex");
}

void VisualMusicModelTest::testSetGetModel()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    m_visualMusicModel->setModel(model);
    QVERIFY2(m_visualMusicModel->model() == model, "Failed setting QAbstractItemModel and getting it back");
}

void VisualMusicModelTest::testInsertScore()
{
    QSignalSpy spy(m_visualMusicModel, SIGNAL(scoreInserted(QModelIndex)));
    m_musicModel->insertScore(0, "Testscore");

    QVERIFY2(m_visualMusicModel->m_rootItem != 0, "Root item is still 0 after insert of score");
    QVERIFY2(m_visualMusicModel->m_visualScoreIndexes.count() == 1,
             "No visual score was inserted");
    QVERIFY2(spy.count() == 1, "Score inserted signal wasn't emitted");
}

void VisualMusicModelTest::testInsertTune()
{
    QSignalSpy spy(m_visualMusicModel, SIGNAL(tuneInserted(QModelIndex)));
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));

    QVERIFY2(m_visualMusicModel->m_visualTuneIndexes.count() == 1,
             "No visual tune was inserted");
    QVERIFY2(spy.count() == 1, "Tune inserted signal wasn't emitted");
}

void VisualMusicModelTest::testInsertPart()
{
    QSignalSpy spy(m_visualMusicModel, SIGNAL(partInserted(QModelIndex)));
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    QModelIndex tuneIndex  = m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));
    m_musicModel->insertPartIntoTune(0, tuneIndex, 8);

    QVERIFY2(m_visualMusicModel->m_visualPartIndexes.count() == 1,
             "No visual part was inserted");
    QVERIFY2(spy.count() == 1, "Part inserted signal wasn't emitted");
}

void VisualMusicModelTest::testInsertMeasure()
{
    QSignalSpy spy(m_visualMusicModel, SIGNAL(measureInserted(QModelIndex)));
    int measureCount = 8;
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    QModelIndex tuneIndex  = m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));
    m_musicModel->insertPartIntoTune(0, tuneIndex, measureCount);

    QVERIFY2(m_visualMusicModel->m_visualMeasureIndexes.count() == measureCount,
             "Not the correct visual measure count was inserted");
    QVERIFY2(spy.count() == measureCount, "Measure inserted wasn't emitted");
}

void VisualMusicModelTest::testInsertSymbol()
{
    QSignalSpy spy(m_visualMusicModel, SIGNAL(symbolInserted(QModelIndex)));
    Q_ASSERT(m_musicModel->instrumentNames().count());
    QString instrumentName = m_musicModel->instrumentNames().at(0);
    Q_ASSERT(m_musicModel->symbolNamesForInstrument(instrumentName).count());
    QString symbolName(m_musicModel->symbolNamesForInstrument(instrumentName).at(0));

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    QModelIndex tuneIndex  = m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));
    QModelIndex partIndex  = m_musicModel->insertPartIntoTune(0, tuneIndex, 8);
    QModelIndex measureIndex = m_musicModel->index(0, 0, partIndex);
    m_musicModel->insertSymbolIntoMeasure(0, measureIndex, symbolName);

    QVERIFY2(m_visualMusicModel->m_visualSymbolIndexes.count() == 1,
             "No visual symbol was inserted");
    QVERIFY2(spy.count() == 1, "Symbol inserted wasn't emitted");
}

void VisualMusicModelTest::testVisualScorePropertiesHolderFromIndex()
{
    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    VisualScore *visualScore = m_visualMusicModel->m_visualScoreIndexes.value(scoreIndex);
    AbstractScorePropertiesItem *scorePropertiesHolder =
            static_cast<AbstractScorePropertiesItem*>(visualScore);

    Q_ASSERT(scorePropertiesHolder);

    QVERIFY2(scorePropertiesHolder ==
             m_visualMusicModel->scorePropertiesItemFromIndex(scoreIndex),
             "score properties holder for index isn't the visual score");
}

void VisualMusicModelTest::testVisualScoreFromIndex()
{
    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    VisualScore *visualScore = m_visualMusicModel->m_visualScoreIndexes.value(scoreIndex);

    Q_ASSERT(visualScore);

    QVERIFY2(visualScore ==
             m_visualMusicModel->visualScoreFromIndex(scoreIndex),
             "visual score for index isn't the visual score");
}

void VisualMusicModelTest::cleanup()
{
    delete m_visualMusicModel;
    delete m_musicModel;
}

void VisualMusicModelTest::init()
{
    m_musicModel = new MusicModel(this);
    m_visualMusicModel = new VisualMusicModel();
    m_visualMusicModel->setModel(m_musicModel);
}

QTEST_MAIN(VisualMusicModelTest)
