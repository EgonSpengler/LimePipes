/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <bar.h>

class BarTest : public QObject
{
    Q_OBJECT
    
public:
    BarTest();
    
private Q_SLOTS:
    void testBarSymbolType();
};

BarTest::BarTest()
{
}

void BarTest::testBarSymbolType()
{
    Bar bar;
    QVERIFY2(bar.symbolType() == LP::Bar, "Failed getting Symbol type from bar");
}

QTEST_APPLESS_MAIN(BarTest)

#include "tst_bartest.moc"
