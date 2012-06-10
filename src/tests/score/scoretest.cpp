#include <QTest>
#include "scoretest.h"
#include "model/score.h"

void ScoreTest::testType()
{
    Score score;
    QVERIFY2( score.type() == ScoreType, "Score returns the wrong type");
}
