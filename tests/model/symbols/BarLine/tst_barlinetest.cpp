/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_barlinetest.h"

void BarLineTest::init()
{
    m_bar = new BarLine();
}

void BarLineTest::cleanup()
{
    delete m_bar;
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

void BarLineTest::testWriteItemDataToStream()
{
    QString data;
    QXmlStreamWriter writer(&data);
    BarLine bar = BarLine();

    bar.writeItemDataToXmlStream(&writer);
    QVERIFY2(!data.contains("<TYPE>", Qt::CaseInsensitive), "Normal Bar has type attribute");
    QVERIFY2(!data.contains("<REPEAT />", Qt::CaseInsensitive), "Normal Bar has repeat attribute");

    data.clear();
    bar = BarLine(BarLine::StartPart);
    bar.writeItemDataToXmlStream(&writer);
    QVERIFY2(data.contains("<TYPE>Start</type>", Qt::CaseInsensitive), "Start Bar doesn't have type attribute");
    QVERIFY2(!data.contains("<REPEAT />", Qt::CaseInsensitive), "Start Bar has repeat attribute");

    data.clear();
    bar = BarLine(BarLine::EndPart);
    bar.writeItemDataToXmlStream(&writer);
    QVERIFY2(data.contains("<TYPE>End</type>", Qt::CaseInsensitive), "End Bar doesn't have type attribute");
    QVERIFY2(!data.contains("<REPEAT />", Qt::CaseInsensitive), "End Bar has repeat attribute");

    data.clear();
    bar = BarLine(BarLine::StartPart);
    bar.setData(true, LP::barLineRepeat);
    bar.writeItemDataToXmlStream(&writer);
    QVERIFY2(data.contains("<TYPE>Start</type>", Qt::CaseInsensitive), "Start Bar doesn't have type attribute");
    QVERIFY2(data.contains("<REPEAT/>", Qt::CaseInsensitive), "Start Bar has no repeat attribute");
}

void BarLineTest::testReadItemFromStream()
{
    readString("<Type>Start</Type>");
    QVERIFY2(m_bar->data(LP::barLineType).value<BarLine::Type>() == BarLine::StartPart, "Failed reading bar line with start of part");
    QVERIFY2(m_bar->data(LP::barLineRepeat).toBool() == false, "Repeat should be false");

    readString("<Repeat/>");
    QVERIFY2(m_bar->data(LP::barLineRepeat).toBool() == true, "Failed reading repeat");
}

void BarLineTest::readString(const QString &string)
{
    QXmlStreamReader reader(string);

    QVERIFY2(!reader.atEnd(), "Reader already at end");
    QVERIFY2(!reader.hasError(), "Reader has error");

    while (reader.name().isEmpty()) {
        reader.readNext();
        if (reader.hasError())
            break;
    }

    QVERIFY2(reader.isStartElement(), "No start element given");

    m_bar->readCurrentElementFromXmlStream(&reader);

    QVERIFY2(!reader.hasError(), "Reader has error after loading");
}

QTEST_APPLESS_MAIN(BarLineTest)

#include "tst_barlinetest.moc"
