/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

class PitchTest : public QObject
{
    Q_OBJECT
    
public:
    PitchTest();
    
private Q_SLOTS:
    void testCase1();
};

PitchTest::PitchTest()
{
}

void PitchTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(PitchTest)

#include "tst_pitchtest.moc"
