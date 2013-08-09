/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>

class VisualMeasureTest : public QObject
{
    Q_OBJECT

public:
    VisualMeasureTest();

private Q_SLOTS:
    void testCase1();
};

VisualMeasureTest::VisualMeasureTest()
{
}

void VisualMeasureTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VisualMeasureTest)

#include "tst_visualmeasuretest.moc"
