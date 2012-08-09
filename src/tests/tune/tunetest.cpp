/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "tunetest.h"
#include "tune.h"

void TuneTest::testType()
{
    Tune tune;
    QVERIFY2( tune.type() == TuneType, "Tune returns the wrong type");
}

