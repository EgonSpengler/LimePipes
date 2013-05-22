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
#include <itemdatatypes.h>

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

void PartTest::testItemSupportsWritingOfData()
{
    QVERIFY2(m_part->itemSupportsWritingOfData(LP::partRepeat), "Part doesn't support writing of part repeat data");
}

QTEST_MAIN(PartTest)

#include "tst_parttest.moc"
