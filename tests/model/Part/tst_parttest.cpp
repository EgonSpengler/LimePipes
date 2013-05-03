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

void PartTest::init()
{
    m_part = new Part();
}

void PartTest::cleanup()
{
    delete m_part;
}

void PartTest::testType()
{
    QVERIFY2(m_part->type() == MusicItem::PartType, "Part item returns the wrong type");
}

QTEST_MAIN(PartTest)

#include "tst_parttest.moc"
