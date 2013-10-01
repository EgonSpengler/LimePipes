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
    void testCase1();

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

void GraphicalScoreItemTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(GraphicalScoreItemTest)

#include "tst_graphicalscoreitemtest.moc"
