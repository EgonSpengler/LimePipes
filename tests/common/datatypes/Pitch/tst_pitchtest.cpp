/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_pitchtest.h"

PitchTest::PitchTest()
{
}

void PitchTest::testCreatePitch()
{
    Pitch pitch;
    QVERIFY2(pitch.staffPos() == 0, "Default pitch has not 0 as staff position");
    QVERIFY2(pitch.name() == "no name", "Failed getting pitch name");
}

void PitchTest::testSetPitchAsQVariant()
{
    QVariant var = QVariant::fromValue<PitchPtr>(PitchPtr(new Pitch()));
    QVERIFY2(var.isValid(), "Failed setting Pitch as QVariant");
}

void PitchTest::testName()
{
    QVERIFY2(Pitch(0, "testname").name() == "testname", "Failed getting pitch name");
}

void PitchTest::testStaffPos()
{
    QVERIFY2(Pitch(2, "testname").staffPos() == 2, "Failed getting pitch staff position");
}

QTEST_APPLESS_MAIN(PitchTest)

#include "tst_pitchtest.moc"
