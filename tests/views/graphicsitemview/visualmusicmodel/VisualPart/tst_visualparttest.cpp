/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>

class VisualPartTest : public QObject
{
    Q_OBJECT

public:
    VisualPartTest();

private Q_SLOTS:
    void testCase1();
};

VisualPartTest::VisualPartTest()
{
}

void VisualPartTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VisualPartTest)

#include "tst_visualparttest.moc"
