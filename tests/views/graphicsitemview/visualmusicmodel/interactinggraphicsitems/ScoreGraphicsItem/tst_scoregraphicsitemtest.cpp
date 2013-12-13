/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QGraphicsScene>
#include <QFocusEvent>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/scoregraphicsitem.h>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/graphicitems/textwidget.h>
#include <graphicsitemview/visualmusicmodel/iteminteraction.h>
#include <iteminteractiondummy.h>

class ScoreGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    ScoreGraphicsItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testRowOfDataRole();
    void testRowAlignmentOfDatarole();
    void testHasItemPositionForDataRole();
    void testRemoveItemPosition();
    void testSetGetItemText();
    void testSetGetItemFont();
    void testSetGetItemColor();
    void testRowCount();
    void testItemTextChanged();
    void testSetData();

private:
    ScoreGraphicsItem *m_scoreItem;
};

ScoreGraphicsItemTest::ScoreGraphicsItemTest()
{
}

void ScoreGraphicsItemTest::init()
{
    m_scoreItem = new ScoreGraphicsItem();
}

void ScoreGraphicsItemTest::cleanup()
{
    delete m_scoreItem;
}

void ScoreGraphicsItemTest::testRowOfDataRole()
{
    QVERIFY2(m_scoreItem->rowOfDataRole(LP::ScoreType) == -1,
             "Wrong default row of non existing data role is wrong");

    m_scoreItem->setItemPosition(LP::ScoreTitle, 1, TextRowWidget::Left);
    QVERIFY2(m_scoreItem->rowOfDataRole(LP::ScoreTitle) == 1,
             "Failed getting right row of data role");
}

void ScoreGraphicsItemTest::testRowAlignmentOfDatarole()
{
    QVERIFY2(m_scoreItem->rowAlignmentOfDataRole(LP::ScoreCopyright) == TextRowWidget::NoAlignment,
             "Wrong default row alignment of non existend data role");

    m_scoreItem->setItemPosition(LP::ScoreArranger, 0, TextRowWidget::Center);
    QVERIFY2(m_scoreItem->rowAlignmentOfDataRole(LP::ScoreArranger) == TextRowWidget::Center,
             "Failed getting right row alignment of data role");
}

void ScoreGraphicsItemTest::testHasItemPositionForDataRole()
{
    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(LP::ScoreArranger) == false,
             "Score item returned true for data role that was not set before");
    m_scoreItem->setItemPosition(LP::ScoreArranger, 0, TextRowWidget::Center);
    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(LP::ScoreArranger),
             "Score item returned false for data role with position");
}

void ScoreGraphicsItemTest::testRemoveItemPosition()
{
    LP::ScoreDataRole testDataRole = LP::ScoreArranger;
    TextRowWidget::RowAlignment testRowAlignment = TextRowWidget::Center;

    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(testDataRole) == false,
             "Score item returned true for data role that was not set before");

    m_scoreItem->setItemPosition(testDataRole, 0, testRowAlignment);
    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(testDataRole),
             "Failed setting item position");

    QString testText("test test");
    m_scoreItem->setItemText(testDataRole, testText);
    int textRowIndex = m_scoreItem->rowOfDataRole(testDataRole);
    TextRowWidget *textRowWidget = m_scoreItem->m_textRows.at(textRowIndex);
    Q_ASSERT(textRowWidget->text(testRowAlignment) == testText);

    m_scoreItem->removeItemPosition(testDataRole);
    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(testDataRole) == false,
             "Failed removing item position");
    QVERIFY2(textRowWidget->text(testRowAlignment).isEmpty(),
             "Text is not empty after removing item");
}

void ScoreGraphicsItemTest::testSetGetItemText()
{
    QString testTitle("test title");
    m_scoreItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    m_scoreItem->setItemText(LP::ScoreTitle, testTitle);

    QVERIFY2(m_scoreItem->itemText(LP::ScoreTitle) == testTitle,
             "Title item has not the right text");
}

void ScoreGraphicsItemTest::testSetGetItemFont()
{
    QFont testFont("Arial", 33);
    m_scoreItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    m_scoreItem->setItemFont(LP::ScoreTitle, testFont);

    QVERIFY2(m_scoreItem->itemFont(LP::ScoreTitle) == testFont,
             "Failed getting font back from score item");
}

void ScoreGraphicsItemTest::testSetGetItemColor()
{
    QColor testColor(Qt::lightGray);
    m_scoreItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    m_scoreItem->setItemColor(LP::ScoreTitle, testColor);

    QVERIFY2(m_scoreItem->itemColor(LP::ScoreTitle) == testColor,
             "Failed getting color back from score item");
}

void ScoreGraphicsItemTest::testRowCount()
{
    QVERIFY2(m_scoreItem->rowCount() == 1, "Wrong initial row count");

    m_scoreItem->setItemPosition(LP::ScoreArranger, 2, TextRowWidget::Center);
    QVERIFY2(m_scoreItem->rowCount() == 3, "Wrong row count after setting item into row > 0");

    m_scoreItem->setItemPosition(LP::ScoreArranger, 1, TextRowWidget::Center);
    QVERIFY2(m_scoreItem->rowCount() == 2,
             "Wrong row count after setting item into lower row index. Empty row wasn't removed");

    m_scoreItem->removeItemPosition(LP::ScoreArranger);
    QVERIFY2(m_scoreItem->rowCount() == 1,
             "Wrong row count after removing last item in row > 0");
}

void ScoreGraphicsItemTest::testItemTextChanged()
{
    m_scoreItem->setItemInteraction(new ItemInteraction);

    // Testdata
    TextRowWidget::RowAlignment testRowAlignment = TextRowWidget::Left;
    QString testText("test text for simulating edit");
    LP::ScoreDataRole testDataRole = LP::ScoreArranger;

    QGraphicsScene scene;
    scene.addItem(m_scoreItem);
    QFocusEvent focusOutEvent(QEvent::FocusOut);
    QFocusEvent focusInEvent(QEvent::FocusIn);
    QSignalSpy textChangedSpy(m_scoreItem, SIGNAL(itemTextChanged(QVariant,int)));
    QSignalSpy dataChangedSpy(m_scoreItem->itemInteraction(), SIGNAL(dataChanged(QVariant,int)));
    m_scoreItem->setItemPosition(testDataRole, 0, testRowAlignment);

    Q_ASSERT(m_scoreItem->m_textRows.count() == 1);
    TextRowWidget *textRow = m_scoreItem->m_textRows.at(0);
    TextWidget * textWidget = textRow->textWidget(testRowAlignment);

    // Simulate edit
    scene.sendEvent(textWidget->textItem(), &focusInEvent);
    textWidget->setText(testText);
    scene.sendEvent(textWidget->textItem(), &focusOutEvent);

    // remove from scene to not delete in cleanup() a second time
    scene.removeItem(m_scoreItem);

    QVERIFY2(textChangedSpy.count() == 1, "Text changed signal wasn't emitted");
    QList<QVariant> arguments = textChangedSpy.takeFirst();
    QVERIFY2(arguments.count() == 2, "Signal has not correct parameter count");
    QString signalText = arguments.at(0).toString();
    QVERIFY2(signalText == testText, "Signal returned not correct text");
    int dataRole = arguments.at(1).toInt();
    QVERIFY2(dataRole == testDataRole, "Signal returned wrong data role argument");

    QVERIFY2(dataChangedSpy.count() == 1, "Item interaction hasn't emitted data changed");
    arguments = dataChangedSpy.takeFirst();
    QVERIFY2(arguments.count() == 2, "Signal has not correct parameter count");
    signalText = arguments.at(0).toString();
    QVERIFY2(signalText == testText, "Signal returned not correct text");
    dataRole = arguments.at(1).toInt();
    QVERIFY2(dataRole == testDataRole, "Signal returned wrong data role argument");

}

void ScoreGraphicsItemTest::testSetData()
{
    QString testData("test data");
    LP::ScoreDataRole testDataRole = LP::ScoreTitle;
    ItemInteractionDummy *interactionDummy = new ItemInteractionDummy();
    QSignalSpy spy(interactionDummy, SIGNAL(setDataCalled()));

    m_scoreItem->setItemPosition(testDataRole, 0, TextRowWidget::Left);
    m_scoreItem->setItemInteraction(interactionDummy);

    m_scoreItem->setData(testData, testDataRole);

    QVERIFY2(spy.count() == 1, "Data changed wasn't called on item interaction (missing parent class call)");
    QVERIFY2(m_scoreItem->itemText(testDataRole) == testData,
             "Item text wasn't set in setData");
}

QTEST_MAIN(ScoreGraphicsItemTest)

#include "tst_scoregraphicsitemtest.moc"
