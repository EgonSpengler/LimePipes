/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <graphicsitemview/interactinggraphicsitems/graphicalscoreitem.h>

class GraphicalScoreItemTest : public QObject
{
    Q_OBJECT

public:
    GraphicalScoreItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetTitle();

private:
    GraphicalScoreItem *m_scoreItem;
};

GraphicalScoreItemTest::GraphicalScoreItemTest()
{
}

void GraphicalScoreItemTest::init()
{
    m_scoreItem = new GraphicalScoreItem();
}

void GraphicalScoreItemTest::cleanup()
{
    delete m_scoreItem;
}

void GraphicalScoreItemTest::testSetTitle()
{
    QString testTitle("test title");
    QVERIFY2(m_scoreItem->m_titleItem == 0, "Title item isn't 0 per default");
    m_scoreItem->setTitle(testTitle);
    QVERIFY2(m_scoreItem->m_titleItem != 0, "Title item is still 0 after setting title");
    QVERIFY2(m_scoreItem->title() == testTitle, "Title item has not the right text");

    m_scoreItem->setTitle("");
    QVERIFY2(m_scoreItem->m_titleItem == 0, "Title item isn't 0 after setting emtpy title");
    QVERIFY2(m_scoreItem->title() == QString(), "Item doesn't return empty title");
}

QTEST_MAIN(GraphicalScoreItemTest)

#include "tst_graphicalscoreitemtest.moc"
