/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>

class VisualSymbolTest : public QObject
{
    Q_OBJECT

public:
    VisualSymbolTest();

private Q_SLOTS:
    void testCase1();
};

VisualSymbolTest::VisualSymbolTest()
{
}

void VisualSymbolTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(VisualSymbolTest)

#include "tst_visualsymboltest.moc"
