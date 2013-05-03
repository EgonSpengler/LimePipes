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

#include "tst_parttest.h"

PartTest::PartTest()
{
}

void PartTest::initTestCase()
{
}

void PartTest::cleanupTestCase()
{
}

void PartTest::testType()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(PartTest)

#include "tst_parttest.moc"
