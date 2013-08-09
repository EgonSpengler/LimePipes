/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>

class VisualTuneTest : public QObject
{
    Q_OBJECT

public:
    VisualTuneTest();

private Q_SLOTS:
    void testCase1();
};

VisualTuneTest::VisualTuneTest()
{
}

void VisualTuneTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VisualTuneTest)

#include "tst_visualtunetest.moc"
