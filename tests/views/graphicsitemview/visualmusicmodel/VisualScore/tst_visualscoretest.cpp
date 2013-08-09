/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>

class VisualScoreTest : public QObject
{
    Q_OBJECT

public:
    VisualScoreTest();

private Q_SLOTS:
    void testCase1();
};

VisualScoreTest::VisualScoreTest()
{
}

void VisualScoreTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VisualScoreTest)

#include "tst_visualscoretest.moc"
