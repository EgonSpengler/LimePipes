#include "lengthtest.h"
#include "length.h"

LengthTest::LengthTest(QObject *parent) :
    QObject(parent)
{
}

void LengthTest::testCase1()
{
    QVERIFY2(true, "testCase1 in LengthTest failed");
}
