/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>

#include "tst_measuretest.h"

MeasureTest::MeasureTest()
{
}

void MeasureTest::initTestCase()
{
}

void MeasureTest::cleanupTestCase()
{
}

void MeasureTest::testType()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(MeasureTest)

#include "tst_measuretest.moc"
