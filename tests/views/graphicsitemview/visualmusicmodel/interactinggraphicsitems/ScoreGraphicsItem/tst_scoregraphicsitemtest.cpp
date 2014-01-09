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
#include <QFont>
#include <QVariant>
#include <common/scoresettings.h>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/scoregraphicsitem.h>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/graphicitems/textwidget.h>
#include <graphicsitemview/visualmusicmodel/iteminteraction.h>
#include <iteminteractiondummy.h>

using namespace Settings::Score;

class ScoreGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    ScoreGraphicsItemTest();

    void testNotifyForDataRole(LP::ScoreDataRole testDataRole, Area testScoreArea);
private Q_SLOTS:
    void init();
    void cleanup();
    void testSettingsCategory();
    void testRegisterUnregisterObserver();
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
    void testNotifyImplementationForTitle();
    void testNotifyImplementationForType();
    void testNotifyImplementationForComposer();
    void testNotifyImplementationForArranger();
    void testNotifyImplementationForCopyright();
    void testNotifyImplementationForYear();

private:
    ScoreGraphicsItem *m_scoreItem;
};

ScoreGraphicsItemTest::ScoreGraphicsItemTest()
{
}

void ScoreGraphicsItemTest::init()
{
    ScoreSettings settings;
    settings.clear();
    settings.sync();

    m_scoreItem = new ScoreGraphicsItem();
}

void ScoreGraphicsItemTest::cleanup()
{
    delete m_scoreItem;
}

void ScoreGraphicsItemTest::testSettingsCategory()
{
    QVERIFY2(m_scoreItem->settingCategory() == Settings::Category::Score,
             "Item has wrong settings category as settings observer");
}

void ScoreGraphicsItemTest::testRegisterUnregisterObserver()
{
    ScoreGraphicsItem *testItem = new ScoreGraphicsItem();

    QVERIFY2(ObservableSettings::isObserverRegistered(testItem),
             "Score item hasn't registered to observable settings with default constructor");

    delete testItem;

    QVERIFY2(ObservableSettings::isObserverRegistered(testItem) == false,
             "Score item hasn't unregistered in destructor");

    testItem = new ScoreGraphicsItem(Settings::Score::Header);
    QVERIFY2(ObservableSettings::isObserverRegistered(testItem),
             "Score item hasn't registered to observable settings with second constructor");

    delete testItem;
}

void ScoreGraphicsItemTest::testRowOfDataRole()
{
    int testRow = 1;
    LP::ScoreDataRole testDataRole = LP::ScoreCopyright;

    QVERIFY2(m_scoreItem->rowIndexOfDataRole(testDataRole) == -1,
             "Wrong default row of non existing data role is wrong");

    m_scoreItem->setItemPosition(testDataRole, testRow, Settings::TextAlignment::Left);
    QVERIFY2(m_scoreItem->rowIndexOfDataRole(testDataRole) == testRow,
             "Failed getting right row of data role");
}

void ScoreGraphicsItemTest::testRowAlignmentOfDatarole()
{
    int testRow = 1;
    LP::ScoreDataRole testDataRole = LP::ScoreCopyright;

    QVERIFY2(m_scoreItem->rowAlignmentOfDataRole(testDataRole) == Settings::TextAlignment::NoAlignment,
             "Wrong default row alignment of non existend data role");

    m_scoreItem->setItemPosition(testDataRole, testRow, Settings::TextAlignment::Center);
    QVERIFY2(m_scoreItem->rowAlignmentOfDataRole(testDataRole) == Settings::TextAlignment::Center,
             "Failed getting right row alignment of data role");
}

void ScoreGraphicsItemTest::testHasItemPositionForDataRole()
{
    int testRow = 1;
    LP::ScoreDataRole testDataRole = LP::ScoreCopyright;

    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(testDataRole) == false,
             "Score item returned true for data role that was not set before");
    m_scoreItem->setItemPosition(testDataRole, testRow, Settings::TextAlignment::Center);
    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(testDataRole),
             "Score item returned false for data role with position");
}

void ScoreGraphicsItemTest::testRemoveItemPosition()
{
    LP::ScoreDataRole testDataRole = LP::ScoreCopyright;
    Settings::TextAlignment testRowAlignment = Settings::TextAlignment::Center;

    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(testDataRole) == false,
             "Score item returned true for data role that was not set before");

    m_scoreItem->setItemPosition(testDataRole, 0, testRowAlignment);
    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(testDataRole),
             "Failed setting item position");

    QString testText("test test");
    m_scoreItem->setItemText(testDataRole, testText);
    int textRowIndex = m_scoreItem->rowIndexOfDataRole(testDataRole);
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
    m_scoreItem->setItemPosition(LP::ScoreTitle, 0, Settings::TextAlignment::Center);
    m_scoreItem->setItemText(LP::ScoreTitle, testTitle);

    QVERIFY2(m_scoreItem->itemText(LP::ScoreTitle) == testTitle,
             "Title item has not the right text");
}

void ScoreGraphicsItemTest::testSetGetItemFont()
{
    QFont testFont("Arial", 33);
    m_scoreItem->setItemPosition(LP::ScoreTitle, 0, Settings::TextAlignment::Center);
    m_scoreItem->setItemFont(LP::ScoreTitle, testFont);

    QVERIFY2(m_scoreItem->itemFont(LP::ScoreTitle) == testFont,
             "Failed getting font back from score item");
}

void ScoreGraphicsItemTest::testSetGetItemColor()
{
    QColor testColor(Qt::lightGray);
    m_scoreItem->setItemPosition(LP::ScoreTitle, 0, Settings::TextAlignment::Center);
    m_scoreItem->setItemColor(LP::ScoreTitle, testColor);

    QVERIFY2(m_scoreItem->itemColor(LP::ScoreTitle) == testColor,
             "Failed getting color back from score item");
}

void ScoreGraphicsItemTest::testRowCount()
{
    m_scoreItem->setItemPosition(LP::ScoreArranger, 2, Settings::TextAlignment::Center);
    QVERIFY2(m_scoreItem->rowCount() == 3, "Wrong row count after setting item into row > 0");

    m_scoreItem->setItemPosition(LP::ScoreArranger, 1, Settings::TextAlignment::Center);
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
    Settings::TextAlignment testRowAlignment = Settings::TextAlignment::Left;
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

    m_scoreItem->setItemPosition(testDataRole, 0, Settings::TextAlignment::Left);
    m_scoreItem->setItemInteraction(interactionDummy);

    m_scoreItem->setData(testData, testDataRole);

    QVERIFY2(spy.count() == 1, "Data changed wasn't called on item interaction (missing parent class call)");
    QVERIFY2(m_scoreItem->itemText(testDataRole) == testData,
             "Item text wasn't set in setData");
}

void ScoreGraphicsItemTest::testNotifyImplementationForTitle()
{
    Area testScoreArea = Area::Header;
    m_scoreItem->setScoreArea(testScoreArea);
    testNotifyForDataRole(LP::ScoreTitle, testScoreArea);
}

void ScoreGraphicsItemTest::testNotifyImplementationForType()
{
    Area testScoreArea = Area::Header;
    m_scoreItem->setScoreArea(testScoreArea);
    testNotifyForDataRole(LP::ScoreType, testScoreArea);
}

void ScoreGraphicsItemTest::testNotifyImplementationForComposer()
{
    Area testScoreArea = Area::Header;
    m_scoreItem->setScoreArea(testScoreArea);
    testNotifyForDataRole(LP::ScoreComposer, testScoreArea);
}

void ScoreGraphicsItemTest::testNotifyImplementationForArranger()
{
    Area testScoreArea = Area::Header;
    m_scoreItem->setScoreArea(testScoreArea);
    testNotifyForDataRole(LP::ScoreArranger, testScoreArea);
}

void ScoreGraphicsItemTest::testNotifyImplementationForCopyright()
{
    Area testScoreArea = Area::Header;
    m_scoreItem->setScoreArea(testScoreArea);
    testNotifyForDataRole(LP::ScoreCopyright, testScoreArea);
}

void ScoreGraphicsItemTest::testNotifyImplementationForYear()
{
    Area testScoreArea = Area::Header;
    m_scoreItem->setScoreArea(testScoreArea);
    testNotifyForDataRole(LP::ScoreYear, testScoreArea);
}

void ScoreGraphicsItemTest::testNotifyForDataRole(LP::ScoreDataRole testDataRole, Area testScoreArea)
{
    ScoreSettings settings(testScoreArea, testDataRole);

    settings.setValue(Enabled, true);
    QVERIFY2(settings.value(Enabled).toBool() == true,
             "Failed set enabled value to settings");

    int testRow = 4;
    if(settings.value(Row).toInt() == testRow)
        testRow++;
    settings.setValue(Row, testRow);
    QVERIFY2(settings.value(Row).toInt() == testRow,
             "Failed set row value in settings");

    Settings::TextAlignment testAlignment = Settings::TextAlignment::Right;
    if (settings.value(Alignment).value<Settings::TextAlignment>() == testAlignment)
        testAlignment = Settings::TextAlignment::Left;
    settings.setValue(Alignment, QVariant::fromValue<Settings::TextAlignment>(testAlignment));
    QVERIFY2(settings.value(Alignment).value<Settings::TextAlignment>() == testAlignment,
             "Failed set alignment value to settings");
    QVERIFY2(m_scoreItem->rowAlignmentOfDataRole(testDataRole) == testAlignment,
             "Test alignment wasn't updated from settings");

    QFont testFont("Arial", 45, QFont::Light);
    if (settings.value(Font).value<QFont>() == testFont)
        testFont = QFont("Times New Roman", 33, QFont::Bold);
    settings.setValue(Font, QVariant::fromValue<QFont>(testFont));
    QVERIFY2(settings.value(Font).value<QFont>() == testFont,
             "Failed set font value to settings");

    QColor testColor("#483673");
    if (settings.value(Color).value<QColor>() == testColor)
        testColor = QColor("#863485");
    settings.setValue(Color, QVariant::fromValue<QColor>(testColor));
    QVERIFY2(settings.value(Color).value<QColor>() == testColor,
             "Failed set color value to settings");

    settings.sync();

    QVERIFY2(m_scoreItem->hasItemPositionForDataRole(testDataRole),
             "Item wasn't set position or it isn't enabled");
    QVERIFY2(m_scoreItem->itemFont(testDataRole) == testFont,
             "Font wasn't updated from settings");
    QVERIFY2(m_scoreItem->itemColor(testDataRole) == testColor,
             "Color wasn't updated from settings");
    QVERIFY2(m_scoreItem->rowIndexOfDataRole(testDataRole) + 1 == testRow,
             "Row wasn't updated from settings");
}

QTEST_MAIN(ScoreGraphicsItemTest)

#include "tst_scoregraphicsitemtest.moc"
