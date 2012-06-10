/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#include <QTest>
#include "bartest.h"
#include "model/bar.h"

void BarTest::testType()
{
    Bar bar;
    QVERIFY2( bar.type() == BarType, "Bar returns the wrong type");
}
