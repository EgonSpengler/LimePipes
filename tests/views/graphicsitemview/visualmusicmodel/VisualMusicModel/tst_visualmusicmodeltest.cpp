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
    QSignalSpy rowSequenceSpy(m_visualMusicModel, SIGNAL(scoreRowSequenceChanged(int)));

    QModelIndex scoreIndex = m_musicModel->appendScore(scoreTitle);

    QVERIFY2(rowSequenceSpy.count() == 1,
             "Row sequence changed signal wasn't emitted after inserting score");
    rowSequenceSpy.clear();

    QVERIFY2(m_visualMusicModel->m_visualItemIndexes.count() == 1,
             "No visual item was inserted");

    VisualItem *scoreItem = m_visualMusicModel->visualItemFromIndex(scoreIndex);
    QVERIFY2(scoreItem->parent() == m_visualMusicModel,
             "Score item has not visual music model as parent");
    QVERIFY2(scoreItem->itemType() == VisualItem::VisualScoreItem,
             "Wrong visual item type returned");

    TestVisualItem *testItem = static_cast<TestVisualItem*>(scoreItem);
    QVERIFY2(testItem, "Can't get testitem from item");

    // Test title was set
    QVERIFY2(testItem->hasData(LP::ScoreTitle),
             "Title of score item wasn't set on creation");
    QVERIFY2(testItem->data(LP::ScoreTitle).toString() == scoreTitle,
             "Wrong title was set");

    // Test data change signal -> abstract item model
    testItem->emitDataChanged(dataChangeTitle, testDataRole);
    QVERIFY2(m_musicModel->data(scoreIndex, testDataRole).toString() == dataChangeTitle,
             "Data wasn't changed in AbstractItemModel");

    // Test row sequence change signal
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
    QSignalSpy interactingItemSpy(&testInteractingItem, SIGNAL(setDataCalled()));
    m_musicModel->setData(scoreIndex, testData, LP::ScoreTitle);

    QVERIFY2(interactingItemSpy.count() == 1,
             "Data changed wasn't called on interacting graphics item");
}

void VisualMusicModelTest::testInsertTune()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");

    QSignalSpy rowSequenceSpy(m_visualMusicModel, SIGNAL(scoreRowSequenceChanged(int)));
    QModelIndex tuneIndex = m_musicModel->insertTuneIntoScore(0, scoreIndex,
                                                              m_musicModel->instrumentNames().at(0));
    QVERIFY2(rowSequenceSpy.count() == 1,
             "Row sequence changed signal wasn't emitted after inserting tune");
    rowSequenceSpy.clear();

    QVERIFY2(m_visualMusicModel->visualItemFromIndex(tuneIndex) != 0,
             "No visual item was inserted");

    VisualItem *tuneItem = m_visualMusicModel->visualItemFromIndex(tuneIndex);
    QVERIFY2(tuneItem->parent() == m_visualMusicModel,
             "Tune item has not visual music model as parent");

    TestVisualItem *testItem = static_cast<TestVisualItem*>(tuneItem);
    QVERIFY2(testItem, "Can't get testitem from item");

    // Test row sequence change signal
    testItem->setGraphicalType(VisualItem::GraphicalRowType);
    testItem->emitRowSequenceChanged();
    QVERIFY2(rowSequenceSpy.count() == 1, "Score row sequence changed signal wasn't emitted");
}

void VisualMusicModelTest::testInsertPart()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());
    QString testInstrumentName(m_musicModel->instrumentNames().at(0));

    bool partRepeatData = true;

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    QModelIndex tuneIndex  = m_musicModel->insertTuneIntoScore(0, scoreIndex, testInstrumentName);

    InstrumentPtr instrument = m_musicModel->data(tuneIndex, LP::TuneInstrument).value<InstrumentPtr>();
    Q_ASSERT(instrument->type() != LP::NoInstrument);

    QSignalSpy rowSequenceSpy(m_visualMusicModel, SIGNAL(scoreRowSequenceChanged(int)));
    QModelIndex partIndex = m_musicModel->insertPartIntoTune(0, tuneIndex, 0, partRepeatData);
    QVERIFY2(rowSequenceSpy.count() == 1,
             "Row sequence changed wasn't emitted after inserting part");
    rowSequenceSpy.clear();

    QVERIFY2(m_visualMusicModel->visualItemFromIndex(tuneIndex) != 0,
             "No visual item was inserted");

    VisualItem *partItem = m_visualMusicModel->visualItemFromIndex(partIndex);
    QVERIFY2(partItem->parent() == m_visualMusicModel,
             "Tune item has not visual music model as parent");

    TestVisualItem *testItem = static_cast<TestVisualItem*>(partItem);
    QVERIFY2(testItem, "Can't get testitem from item");

    QVERIFY2(testItem->hasData(LP::PartStaffType),
             "Staff type wasn't set in VisualItem");
    QVERIFY2(testItem->data(LP::PartStaffType).value<StaffType>() == instrument->staffType(),
             "VisualItem has wrong staff type");
    QVERIFY2(testItem->hasData(LP::PartRepeat),
             "Repeat data wasn't set");
    QVERIFY2(testItem->data(LP::PartRepeat).toBool() == partRepeatData,
             "Repeat wasn't set in new VisualPart");

    // Test row sequence change signal
    testItem->emitRowSequenceChanged();
    QVERIFY2(rowSequenceSpy.count() == 1, "Score row sequence changed signal wasn't emitted");
}

void VisualMusicModelTest::testInsertMeasure()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());

    QModelIndex scoreIndex = m_musicModel->insertScore(0, "Test score");
    QModelIndex tuneIndex  = m_musicModel->insertTuneIntoScore(0, scoreIndex, m_musicModel->instrumentNames().at(0));
    QModelIndex partIndex  = m_musicModel->appendPartToTune(tuneIndex, 0);

    QSignalSpy rowSequenceSpy(m_visualMusicModel, SIGNAL(scoreRowSequenceChanged(int)));
    QModelIndex measureIndex = m_musicModel->appendMeasureToPart(partIndex);

    QVERIFY2(rowSequenceSpy.count() == 0,
             "Row sequence changed wasn emitted after inserting measure");
    rowSequenceSpy.clear();

    QVERIFY2(m_visualMusicModel->visualItemFromIndex(measureIndex) != 0,
             "No visual item was inserted");

    VisualItem *measureItem = m_visualMusicModel->visualItemFromIndex(measureIndex);
    QVERIFY2(measureItem->parent() == m_visualMusicModel,
             "Measure item has not visual music model as parent");

    TestVisualItem *testItem = static_cast<TestVisualItem*>(measureItem);
    QVERIFY2(testItem, "Can't get testitem from item");
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

    QSignalSpy rowSequenceSpy(m_visualMusicModel, SIGNAL(scoreRowSequenceChanged(int)));
    QModelIndex symbolIndex = m_musicModel->insertSymbolIntoMeasure(0, measureIndex, symbolName);

    QVERIFY2(rowSequenceSpy.count() == 0,
             "Row sequence changed wasn emitted after inserting measure");
    rowSequenceSpy.clear();

    QVERIFY2(m_visualMusicModel->visualItemFromIndex(symbolIndex) != 0,
             "No visual item was inserted");

    VisualItem *symbolItem = m_visualMusicModel->visualItemFromIndex(symbolIndex);
    QVERIFY2(symbolItem->parent() == m_visualMusicModel,
             "Measure item has not visual music model as parent");

    TestVisualItem *testItem = static_cast<TestVisualItem*>(symbolItem);
    QVERIFY2(testItem, "Can't get testitem from item");

    if (m_musicModel->data(symbolIndex, LP::SymbolCategory).isValid()) {
        QVERIFY2(testItem->hasData(LP::SymbolCategory),
                 "Symbol category data wasn't set");
        QVERIFY2(testItem->data(LP::SymbolCategory).value<SymbolCategory>() ==
                 m_musicModel->data(symbolIndex, LP::SymbolCategory).value<SymbolCategory>(),
                 "VisualItem has wrong symbol category");
    }

    if (m_musicModel->data(symbolIndex, LP::SymbolType).isValid()) {
        QVERIFY2(testItem->hasData(LP::SymbolType),
                 "Symbol type data wasn't set");
        QVERIFY2(testItem->data(LP::SymbolType).toInt() ==
                 m_musicModel->data(symbolIndex, LP::SymbolType).toInt(),
                 "VisualItem has wrong symbol type");
    }

    if (m_musicModel->data(symbolIndex, LP::SymbolName).isValid()) {
        QVERIFY2(testItem->hasData(LP::SymbolName),
                 "Symbol name data wasn't set");
        QVERIFY2(testItem->data(LP::SymbolName).toString() ==
                 m_musicModel->data(symbolIndex, LP::SymbolName).toString(),
                 "VisualItem has wrong symbol name");
    }

    if (m_musicModel->data(symbolIndex, LP::SymbolLength).isValid()) {
        QVERIFY2(testItem->hasData(LP::SymbolLength),
                 "Symbol length data wasn't set");
        QVERIFY2(testItem->data(LP::SymbolLength).value<Length::Value>() ==
                 m_musicModel->data(symbolIndex, LP::SymbolLength).value<Length::Value>(),
                 "VisualItem has wrong symbol length");
    }

    if (m_musicModel->data(symbolIndex, LP::SymbolPitch).isValid()) {
        QVERIFY2(testItem->hasData(LP::SymbolPitch),
                 "Symbol pitch data wasn't set");
        QVERIFY2(testItem->data(LP::SymbolPitch).value<PitchPtr>() ==
                 m_musicModel->data(symbolIndex, LP::SymbolPitch).value<PitchPtr>(),
                 "VisualItem has wrong symbol pitch");
    }
}

void VisualMusicModelTest::testInsertChildItemCallOnVisualItem()
{
    Q_ASSERT(m_musicModel->instrumentNames().count());
    QString instrumentName = m_musicModel->instrumentNames().at(0);
    QString scoreTitle("Testscore");
    QModelIndex scoreIndex = m_musicModel->appendScore(scoreTitle);
    // Append two tunes for row > 0
    m_musicModel->appendTuneToScore(scoreIndex, instrumentName);
    QModelIndex tuneIndex = m_musicModel->appendTuneToScore(scoreIndex, instrumentName);
    Q_ASSERT(tuneIndex.isValid());

    VisualItem *scoreItem = m_visualMusicModel->visualItemFromIndex(scoreIndex);
    VisualItem *tuneItem = m_visualMusicModel->visualItemFromIndex(tuneIndex);
    TestVisualItem *testScoreItem = static_cast<TestVisualItem*>(scoreItem);
    QVERIFY2(testScoreItem, "Can't get testitem from score item");

    QVERIFY2(testScoreItem->insertChildItemCalled() == true,
             "Insert child item wasn't called");
    QVERIFY2(testScoreItem->rowOfChildToInsert() == tuneIndex.row(),
             "Insert child item was called with wrong row");
    QVERIFY2(testScoreItem->childItemToInsert() == tuneItem,
             "Insert child item was called with wrong child item");
}

QTEST_MAIN(VisualMusicModelTest)
