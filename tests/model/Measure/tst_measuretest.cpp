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

void MeasureTest::init()
{
    m_measure = new Measure();
}

void MeasureTest::cleanup()
{
    delete m_measure;
}

void MeasureTest::testType()
{
    QVERIFY2(m_measure->type() == MusicItem::MeasureType, "Measure item returns the wrong type");
}

QTEST_MAIN(MeasureTest)

#include "tst_measuretest.moc"
