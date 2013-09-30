/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <views/graphicsitemview/visualmusicmodel/visualscore.h>

class GraphicalScoreDummy : public GraphicalScoreInterface
{
};

class VisualScoreTest : public QObject
{
    Q_OBJECT

public:
    VisualScoreTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testSetGetGraphicalScore();

private:
    VisualScore *m_visualScore;
};

VisualScoreTest::VisualScoreTest()
{
}

void VisualScoreTest::init()
{
    m_visualScore = new VisualScore();
}

void VisualScoreTest::cleanup()
{
    delete m_visualScore;
}

void VisualScoreTest::testType()
{
    QVERIFY2(m_visualScore->type() == AbstractVisualItem::VisualScoreItem, "Visual score returned wrong type");
}

void VisualScoreTest::testSetGetGraphicalScore()
{
    QVERIFY2(m_visualScore->graphicalScore() == 0, "Graphical score wasn't initialized to 0");
    GraphicalScoreInterface *graphicalScore = new GraphicalScoreDummy();
    m_visualScore->setGraphicalScore(graphicalScore);
    QVERIFY2(graphicalScore == m_visualScore->graphicalScore(), "Can't get right graphical score back");
    delete graphicalScore;
}

QTEST_APPLESS_MAIN(VisualScoreTest)

#include "tst_visualscoretest.moc"
