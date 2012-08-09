#include "pitchtest.h"
#include "pitch.h"

PitchTest::PitchTest(QObject *parent) :
    QObject(parent)
{
}

void PitchTest::testCase1()
{
    QVERIFY2(true, "testCase1 in PitchTest failed.");
}
