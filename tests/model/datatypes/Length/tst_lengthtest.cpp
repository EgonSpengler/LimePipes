/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <length.h>

class LengthTest : public QObject
{
    Q_OBJECT
    
public:
    LengthTest();
    
private Q_SLOTS:
    void testCase1();
};

LengthTest::LengthTest()
{
}

void LengthTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(LengthTest)

#include "tst_lengthtest.moc"
