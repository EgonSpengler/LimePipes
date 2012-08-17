/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

class BarTest : public QObject
{
    Q_OBJECT
    
public:
    BarTest();
    
private Q_SLOTS:
    void testCase1();
};

BarTest::BarTest()
{
}

void BarTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(BarTest)

#include "tst_bartest.moc"
