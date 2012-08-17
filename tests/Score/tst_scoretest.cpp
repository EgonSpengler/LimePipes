/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "score.h"

class ScoreTest : public QObject
{
    Q_OBJECT
    
public:
    ScoreTest();
    
private Q_SLOTS:
    void testType();
};

ScoreTest::ScoreTest()
{
}

void ScoreTest::testType()
{
    Score score;
    QVERIFY2( score.type() == ScoreType, "Score returns the wrong type");
}

QTEST_APPLESS_MAIN(ScoreTest)

#include "tst_scoretest.moc"
