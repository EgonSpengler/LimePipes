/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <timesignature.h>

class TimeSignatureTest : public QObject
{
    Q_OBJECT
    
public:
    TimeSignatureTest();
    
private Q_SLOTS:
    void testBeatCount();
    void testBeatUnit();
};

TimeSignatureTest::TimeSignatureTest()
{
}

void TimeSignatureTest::testBeatCount()
{
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_2_2) == 2, "Fail for 2/2");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_2_4) == 2, "Fail for 2/4");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_3_4) == 3, "Fail for 3/4");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_4_4) == 4, "Fail for 4/4");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_3_8) == 3, "Fail for 3/8");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_6_8) == 6, "Fail for 6/8");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_9_8) == 9, "Fail for 9/8");
    QVERIFY2(TimeSignature::beatCount(TimeSignature::_12_8) == 12, "Fail for 12/8");
}

void TimeSignatureTest::testBeatUnit()
{
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_2_2) == 2, "Fail for 2/2");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_2_4) == 4, "Fail for 2/4");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_3_4) == 4, "Fail for 3/4");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_4_4) == 4, "Fail for 4/4");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_3_8) == 8, "Fail for 3/8");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_6_8) == 8, "Fail for 6/8");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_9_8) == 8, "Fail for 9/8");
    QVERIFY2(TimeSignature::beatUnit(TimeSignature::_12_8) == 8, "Fail for 12/8");
}

QTEST_APPLESS_MAIN(TimeSignatureTest)

#include "tst_timesignaturetest.moc"
