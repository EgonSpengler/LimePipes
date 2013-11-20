/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <graphicsitemview/interactinggraphicsitems/scoregraphicsitem.h>

class ScoreGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    ScoreGraphicsItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
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

QTEST_MAIN(ScoreGraphicsItem)

#include "tst_scoregraphicsitemtest.moc"
