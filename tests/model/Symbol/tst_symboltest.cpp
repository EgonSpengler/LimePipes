/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <common/defines.h>
#include <common/itemdataroles.h>
#include "tst_symboltest.h"

void SymbolTest::init()
{
    m_symbol = new TestSymbol();
}

void SymbolTest::cleanup()
{
    delete m_symbol;
}

void SymbolTest::testConstructor()
{
    QVERIFY2(m_symbol->data(LP::SymbolType).toInt() == LP::NoSymbolType, "Wrong Symbol id in default constructor");
    QVERIFY2(m_symbol->data(LP::SymbolName).isValid(), "Symbol has no name in default constructor");

    Symbol symbol(333, "Testsymbol");
    QVERIFY2(symbol.data(LP::SymbolType).toInt() == 333, "Failed setting symbol Id in constructor");
    QVERIFY2(symbol.data(LP::SymbolName) == "Testsymbol", "Failed setting symbol name in constructor");
}

void SymbolTest::testType()
{
    QVERIFY2( m_symbol->type() == MusicItem::SymbolType, "Symbol returns the wrong type");
}

void SymbolTest::testChildType()
{
    QVERIFY2( m_symbol->childType() == MusicItem::NoItemType, "The child itemtype of Symbol is not NoItem type");
}

void SymbolTest::testSymbolType()
{
    QVERIFY2(m_symbol->symbolType() == LP::NoSymbolType, "Failed to get the default symbol type");
}

void SymbolTest::testHasPitch()
{
    delete m_symbol;
    m_symbol = new Symbol();
    QVERIFY2(m_symbol->hasPitch() == false, "Failed, default symbol should have no pitch");

    delete m_symbol;
    m_symbol = new TestSymbol();
    QVERIFY2(m_symbol->hasPitch(), "Failed, symbol with pitch returned false");
}

void SymbolTest::testHasLength()
{
    delete m_symbol;
    m_symbol = new Symbol();
    QVERIFY2(m_symbol->hasLength() == false, "Failed, default symbol should have no length");

    delete m_symbol;
    m_symbol = new TestSymbol();
    QVERIFY2(m_symbol->hasLength(), "Failed, symbol with length returned false");
}

void SymbolTest::testWriteToXmlStream()
{
    QString data;
    QXmlStreamWriter writer(&data);
    PitchPtr testPitch(new Pitch(2, "test pitch name"));
    Length::Value testLength(Length::_32);

    TestSymbol testSymbol;
    Q_ASSERT(testSymbol.itemSupportsWritingOfData(LP::SymbolPitch));
    Q_ASSERT(testSymbol.itemSupportsWritingOfData(LP::SymbolLength));

    testSymbol.setData(QVariant::fromValue<PitchPtr>(testPitch), LP::SymbolPitch);
    testSymbol.setData(QVariant::fromValue<Length::Value>(testLength), LP::SymbolLength);

    testSymbol.writeItemDataToXmlStream(&writer);
    QString nameTag  = patternForTag("NAME", testSymbol.data(LP::SymbolName).toString());
    QString pitchTag = patternForTag("PITCH", testPitch->name());
    QString lengthTag = patternForTag("LENGTH", QString::number(testLength, 10));

    QVERIFY2(!data.contains(nameTag, Qt::CaseInsensitive), "Symbol tag was found");
    QVERIFY2(data.contains(pitchTag, Qt::CaseInsensitive), "No pitch tag found");
    QVERIFY2(data.contains(lengthTag, Qt::CaseInsensitive), "No length tag found");
}

QString SymbolTest::patternForTag(const QString &tagname, const QString &data)
{
    QString tag = QString("<") + tagname + ">" + data;
    return tag;
}

void SymbolTest::testReadFromXmlStream()
{
    Length::Value length = Length::_64;
    Q_ASSERT(length != m_symbol->length());

    readTextElement("LENGTH", QString::number(length));
    QVERIFY2(m_symbol->length() == length, "Failed reading length");
}

void SymbolTest::readTextElement(const QString &tagName, const QString &elementText)
{
    QString data = QString("<") + tagName + ">" + elementText + "</" + tagName +">";
    readString(data);
}

void SymbolTest::readString(const QString &string)
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

    m_symbol->readCurrentElementFromXmlStream(&reader);

    QVERIFY2(!reader.hasError(), "Reader has error after loading");
}

QTEST_MAIN(SymbolTest)

#include "tst_symboltest.moc"
