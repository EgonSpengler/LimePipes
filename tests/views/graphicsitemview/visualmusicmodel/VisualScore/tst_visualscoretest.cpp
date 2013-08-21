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

class VisualScoreTest : public QObject
{
    Q_OBJECT

public:
    VisualScoreTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();

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

QTEST_APPLESS_MAIN(VisualScoreTest)

#include "tst_visualscoretest.moc"
