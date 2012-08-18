/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <score.h>

class ScoreTest : public QObject
{
    Q_OBJECT
    
public:
    ScoreTest() : m_score(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testParentType();

private:
    Score *m_score;
};

void ScoreTest::init()
{
    m_score = new Score();
}

void ScoreTest::cleanup()
{
    delete m_score;
}

void ScoreTest::testType()
{
    QVERIFY2( m_score->type() == ScoreType, "Score returns the wrong type");
}

void ScoreTest::testParentType()
{
    QVERIFY2(m_score->parentType() == NoItemType, "The parent itemtype of score is not NoItemType");
}

QTEST_APPLESS_MAIN(ScoreTest)

#include "tst_scoretest.moc"
