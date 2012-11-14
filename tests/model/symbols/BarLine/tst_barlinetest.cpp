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
    void testConstructor();
    void testBarSymbolType();
    void testWritingOfData();
    void testRepeat();
};

BarLineTest::BarLineTest()
{
}

void BarLineTest::testConstructor()
{
    BarLine barLine = BarLine(BarLine::StartPart);
    QVERIFY2(barLine.data(LP::barLineType).isValid(), "No valid barline type");
    QVERIFY2(barLine.data(LP::barLineType).canConvert<BarLine::Type>(), "Can't convert into BarLine type");
    QVERIFY2(barLine.data(LP::barLineType).value<BarLine::Type>() == BarLine::StartPart, "Wrong value returned");

    QVERIFY2(barLine.data(LP::barLineRepeat).isValid(), "No valid barline repeat data");
    QVERIFY2(barLine.data(LP::barLineRepeat).canConvert<bool>(), "Can't convert bar line repeat data into bool");
    QVERIFY2(barLine.data(LP::barLineRepeat).value<bool>() == false, "Default barline must be with no repeat");

    // Symbol flags
    QVERIFY2(barLine.hasPitch() == false, "Bar line can't have pitch");
    QVERIFY2(barLine.hasLength() == false, "Bar line can't have length");
}

void BarLineTest::testBarSymbolType()
{
    BarLine barLine(BarLine::StartPart);
    QVERIFY2(barLine.symbolType() == LP::BarLine, "Failed getting Symbol type from bar");
}

void BarLineTest::testWritingOfData()
{
    BarLine bar;
    QVERIFY2(bar.itemSupportsWritingOfData(LP::barLineType) == false, "Bar line type should not be writable data");
    QVERIFY2(bar.itemSupportsWritingOfData(LP::barLineRepeat) == true, "Bar line repeat should be writable");
}

void BarLineTest::testRepeat()
{
    BarLine *bar = new BarLine(BarLine::StartPart);
    bar->setData(true, LP::barLineRepeat);
    QVERIFY2(bar->data(LP::barLineRepeat).toBool() == true, "Failed setting repeat bar");

    delete bar;
    bar = new BarLine(BarLine::Normal);
    QVERIFY2(bar->data(LP::barLineRepeat).toBool() == false, "Default repeat value of normal bar is not false");
    bar->setData(true, LP::barLineRepeat);
    QVERIFY2(bar->data(LP::barLineRepeat).toBool() == false, "Normal bars can't have a repeat value");
}

QTEST_APPLESS_MAIN(BarLineTest)

#include "tst_barlinetest.moc"
