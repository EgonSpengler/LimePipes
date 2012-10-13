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
#include <timesignature.h>
#include <itemdatatypes.h>

class ScoreTest : public QObject
{
    Q_OBJECT
    
public:
    ScoreTest() : m_score(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testChildType();
    void testSetData();
    void testConstructor();
    void testSetGetTitle();

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
    QVERIFY2( m_score->type() == MusicItem::ScoreType, "Score returns the wrong type");
}

void ScoreTest::testChildType()
{
    QVERIFY2(m_score->childType() == MusicItem::TuneType, "The child itemtype of score is not TuneType");
}

void ScoreTest::testSetData()
{
    m_score->setData("test title", LP::scoreTitle);
    QVERIFY2(m_score->data(LP::scoreTitle) == "test title", "Failed set title");

    m_score->setData("test composer", LP::scoreComposer);
    QVERIFY2(m_score->data(LP::scoreComposer) == "test composer", "Failed set composer");

    m_score->setData("test arranger", LP::scoreArranger);
    QVERIFY2(m_score->data(LP::scoreArranger) == "test arranger", "Failed set arranger");

    m_score->setData("test year", LP::scoreYear);
    QVERIFY2(m_score->data(LP::scoreYear) == "test year", "Failed set year");

    m_score->setData("test copyright", LP::scoreCopyright);
    QVERIFY2(m_score->data(LP::scoreCopyright) == "test copyright", "Failed set copyright");

    m_score->setData(QVariant::fromValue(TimeSignature(TimeSignature::_3_4)), LP::scoreTimeSignature);
    QVERIFY2(m_score->data(LP::scoreTimeSignature).value<TimeSignature>().signature() == TimeSignature::_3_4, "Failed set time signature");
}

void ScoreTest::testConstructor()
{
    delete m_score;
    m_score = new Score(QString("The Title"));
    QVERIFY2(m_score->data(LP::scoreTitle) == "The Title", "Failed setting the score title in the constructor");
    QVERIFY2(m_score->type() == MusicItem::ScoreType, "Score returns the wrong type");
    QVERIFY2(m_score->childType() == MusicItem::TuneType, "The child itemtype of score is not TuneType");
}

void ScoreTest::testSetGetTitle()
{
    m_score->setTitle(QString("New Title"));
    QVERIFY2(m_score->data(LP::scoreTitle) == "New Title", "Failed setting title");
    QVERIFY2(m_score->title() == "New Title", "Failed getting title");
}

QTEST_APPLESS_MAIN(ScoreTest)

#include "tst_scoretest.moc"
