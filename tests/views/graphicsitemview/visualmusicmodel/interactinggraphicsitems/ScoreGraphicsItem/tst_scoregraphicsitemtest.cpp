/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/scoregraphicsitem.h>

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
    void testSetTitle();

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

void ScoreGraphicsItemTest::testSetTitle()
{
    QString testTitle("test title");
    m_scoreItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    m_scoreItem->setItemText(LP::ScoreTitle, testTitle);
    QVERIFY2(m_scoreItem->itemText(LP::ScoreTitle) != 0, "Title item is still 0 after setting title");
    QVERIFY2(m_scoreItem->itemText(LP::ScoreTitle) == testTitle, "Title item has not the right text");

    m_scoreItem->setItemText(LP::ScoreTitle, "");
    QVERIFY2(m_scoreItem->itemText(LP::ScoreTitle) == 0, "Title item isn't 0 after setting emtpy title");
    QVERIFY2(m_scoreItem->itemText(LP::ScoreTitle) == QString(), "Item doesn't return empty title");
}

QTEST_MAIN(ScoreGraphicsItemTest)

#include "tst_scoregraphicsitemtest.moc"
