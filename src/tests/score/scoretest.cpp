/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QTest>
#include "scoretest.h"
#include "model/score.h"

void ScoreTest::testType()
{
    Score score;
    QVERIFY2( score.type() == ScoreType, "Score returns the wrong type");
}
