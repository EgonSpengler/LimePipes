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
#include <views/graphicsitemview/visualmusicmodel/visualmusicmodel.h>
#include "testvisualitem.h"
#include "testinteractingitem.h"
#include "testvisualitemfactory.h"
#include "tst_visualmusicmodeltest.h"

Q_IMPORT_PLUGIN(GreatHighlandBagpipe)

VisualMusicModelTest::VisualMusicModelTest(QObject *parent)
    : QObject(parent),
      m_musicModel(0),
      m_visualMusicModel(0),
      m_itemFactory(0)
{
    qRegisterMetaType<QModelIndex>("QModelIndex");
}

void VisualMusicModelTest::init()
{
    m_musicModel = new MusicModel(this);
    m_itemFactory = new TestVisualItemFactory();
    m_visualMusicModel = new VisualMusicModel(m_itemFactory);
    m_visualMusicModel->setModel(m_musicModel);
}

void VisualMusicModelTest::cleanup()
{
    delete m_visualMusicModel;
    delete m_itemFactory;
    delete m_musicModel;
}

void VisualMusicModelTest::testSetGetModel()
{
    QStandardItemModel *model = new QStandardItemModel(this);
    m_visualMusicModel->setModel(model);
    QVERIFY2(m_visualMusicModel->model() == model, "Failed setting QAbstractItemModel and getting it back");
}

void VisualMusicModelTest::testVisualItemFromIndex()
{
    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    VisualItem *visualItem = m_visualMusicModel->m_visualItemIndexes.value(scoreIndex);

    Q_ASSERT(visualItem);

    QVERIFY2(visualItem == m_visualMusicModel->visualItemFromIndex(scoreIndex),
             "visual item for index isn't the right visual item");
}

void VisualMusicModelTest::testInsertScore()
{
    QString scoreTitle("Testscore");
    QString dataChangeTitle("New title");
    LP::ScoreDataRole testDataRole = LP::ScoreTitle;
    QModelIndex scoreIndex = m_musicModel->appendScore(scoreTitle);

    QVERIFY2(m_visualMusicModel->m_visualItemIndexes.count() == 1,
             "No visual item was inserted");

    VisualItem *scoreItem = m_visualMusicModel->visualItemFromIndex(scoreIndex);
    QVERIFY2(scoreItem->parent() == m_visualMusicModel,
             "Score item has not visual music model as parent");

    TestVisualItem *testItem = static_cast<TestVisualItem*>(scoreItem);
    QVERIFY2(testItem, "Can't get testitem from item");

    // Test data change signal -> abstract item model
    testItem->emitDataChanged(dataChangeTitle, testDataRole);
    QVERIFY2(m_musicModel->data(scoreIndex, testDataRole).toString() == dataChangeTitle,
             "Data wasn't changed in AbstractItemModel");

    // Test row sequence change signal
    QSignalSpy rowSequenceSpy(m_visualMusicModel, SIGNAL(scoreRowSequenceChanged(int)));
    testItem->setGraphicalType(VisualItem::GraphicalRowType);
    testItem->emitRowSequenceChanged();
    QVERIFY2(rowSequenceSpy.count() == 1, "Score row sequence changed signal wasn't emitted");
}

void VisualMusicModelTest::testScoreDataChanged()
{
    QString testData("Test title");
    TestInteractingItem testInteractingItem;
    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    VisualItem *visualItem = m_visualMusicModel->visualItemFromIndex(scoreIndex);
    Q_ASSERT(visualItem);
    visualItem->setGraphicalType(VisualItem::GraphicalInlineType);
    visualItem->setInlineGraphic(&testInteractingItem);
    QSignalSpy spy(&testInteractingItem, SIGNAL(setDataCalled()));
    m_musicModel->setData(scoreIndex, testData, LP::ScoreTitle);

    QVERIFY2(spy.count() == 1, "data changed wasn't called on visual item");
}

void VisualMusicModelTest::testInsertTune()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));
}

void VisualMusicModelTest::testInsertPart()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    QModelIndex tuneIndex  = m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));
    m_musicModel->insertPartIntoTune(0, tuneIndex, 8);
}

void VisualMusicModelTest::testInsertMeasure()
{
    int measureCount = 8;
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    QModelIndex tuneIndex  = m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));
    m_musicModel->insertPartIntoTune(0, tuneIndex, measureCount);
}

void VisualMusicModelTest::testInsertSymbol()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());
    QString instrumentName = m_musicModel->instrumentNames().at(0);
    Q_ASSERT(m_musicModel->symbolNamesForInstrument(instrumentName).count());
    QString symbolName(m_musicModel->symbolNamesForInstrument(instrumentName).at(0));

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    QModelIndex tuneIndex  = m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));
    QModelIndex partIndex  = m_musicModel->insertPartIntoTune(0, tuneIndex, 8);
    QModelIndex measureIndex = m_musicModel->index(0, 0, partIndex);
    m_musicModel->insertSymbolIntoMeasure(0, measureIndex, symbolName);
}

QTEST_MAIN(VisualMusicModelTest)
