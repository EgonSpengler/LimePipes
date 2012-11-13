/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <barline.h>

class BarLineTest : public QObject
{
    Q_OBJECT

public:
    BarLineTest();

private Q_SLOTS:
    void testBarSymbolType();
};

BarLineTest::BarLineTest()
{
}

void BarLineTest::testBarSymbolType()
{
    BarLine barLine;
    QVERIFY2(barLine.symbolType() == LP::BarLine, "Failed getting Symbol type from bar");
}


QTEST_APPLESS_MAIN(BarLineTest)

#include "tst_barlinetest.moc"
