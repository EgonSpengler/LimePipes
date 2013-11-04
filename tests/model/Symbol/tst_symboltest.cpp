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
#include <interfaceglobals.h>
#include <itemdatatypes.h>
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

void SymbolTest::testHasGraphic()
{
    QVERIFY2(m_symbol->hasGraphic() == false, "Fail, symbol has graphic but it shouldn't have one");
    TestSymbol *testSymbol = static_cast<TestSymbol*>(m_symbol);
    Q_ASSERT(testSymbol);
    testSymbol->setGraphicBuilder(new TestGraphicBuilder(m_symbol));
    QVERIFY2(m_symbol->hasGraphic() == true, "Fail, symbol has no graphic");
}

void SymbolTest::testSetSymbolGraphicBuilder()
{
    TestGraphicBuilder *graphicBuilder = new TestGraphicBuilder(m_symbol);

    TestSymbol *testSymbol = static_cast<TestSymbol*>(m_symbol);
    Q_ASSERT(testSymbol);
    QVERIFY2(testSymbol->data(LP::SymbolGraphic).isValid() == false, "Fail, symbol has already set a graphic");

    QSignalSpy spy(graphicBuilder, SIGNAL(updateSymbolGraphicCalled()));
    testSymbol->setGraphicBuilder(graphicBuilder);
    QVERIFY2(spy.count() != 0, "Fail, updateSymbolGraphic wasn't called");

    QVERIFY2(testSymbol->data(LP::SymbolGraphic).isValid(), "Symbol graphic wasn't set with graphic builder");
    QVERIFY2(testSymbol->data(LP::SymbolGraphic).canConvert<SymbolGraphicPtr>(), "graphic data isn't a symbol graphic");
}

void SymbolTest::testCreateSymbolPixmaps()
{
    int testLineHeight = 55;
    TestGraphicBuilder *graphicBuilder = new TestGraphicBuilder(m_symbol);
    QSignalSpy spy(graphicBuilder, SIGNAL(createPixmapsCalled()));
    TestSymbol *testSymbol = static_cast<TestSymbol*>(m_symbol);
    Q_ASSERT(testSymbol);
    testSymbol->setGraphicBuilder(graphicBuilder);
    m_symbol->createSymbolPixmaps(testLineHeight);
    QVERIFY2(spy.count() == 1, "graphic builder's create pixmaps wasn't called");
    QVERIFY2(graphicBuilder->lineHeight() == testLineHeight, "line height wasn't set for graphics builder");
}

void SymbolTest::testAfterWritingDataCall()
{
    TestGraphicBuilder *graphicBuilder = new TestGraphicBuilder(m_symbol);
    TestSymbol *testSymbol = static_cast<TestSymbol*>(m_symbol);
    Q_ASSERT(testSymbol);
    testSymbol->setGraphicBuilder(graphicBuilder);

    QSignalSpy spy(testSymbol, SIGNAL(afterWritingDataCalled()));
    m_symbol->setData(Length::_32, LP::SymbolLength);
    QVERIFY2(spy.count() != 0, "Symbol graphic wasn't updated after setting data");
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
