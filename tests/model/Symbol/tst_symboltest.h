/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLTEST_H
#define SYMBOLTEST_H

#include <QObject>
#include <symbol.h>
#include <symbolgraphicbuilder.h>

namespace {

class TestGraphicBuilder :  public QObject,
        public SymbolGraphicBuilder
{
    Q_OBJECT
public:
    TestGraphicBuilder(MusicItem *item)
        : SymbolGraphicBuilder(item)
    {}
    ~TestGraphicBuilder() {}

    void createPixmaps(int lineHeight) {
        Q_UNUSED(lineHeight)
        emit createPixmapsCalled();
    }
    void updateSymbolGraphic() { emit updateSymbolGraphicCalled(); }

    bool isSymbolGraphicAffectedByDataRole(int role) { Q_UNUSED(role) return true; }

signals:
    void createPixmapsCalled();
    void updateSymbolGraphicCalled();
};

class TestSymbol :  public QObject,
        public Symbol
{
    Q_OBJECT
public:
    TestSymbol()
        : Symbol()
    {
        setSymbolOptions(Symbol::HasPitch |
                         Symbol::HasLength);
        initData(QVariant::fromValue<Length::Value>(Length::_16), LP::SymbolLength);
    }

    void setGraphicBuilder(SymbolGraphicBuilder *builder) { setSymbolGraphicBuilder(builder); }

protected:
    void afterWritingData(int role) { Q_UNUSED(role) emit afterWritingDataCalled(); }

signals:
    void afterWritingDataCalled();
};

}

class SymbolTest : public QObject
{
    Q_OBJECT
    
public:
    SymbolTest(): m_symbol(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testType();
    void testChildType();
    void testSymbolType();
    void testHasPitch();
    void testHasLength();
    void testHasGraphic();
    void testSetSymbolGraphicBuilder();
    void testCreateSymbolPixmaps();
    void testAfterWritingDataCall();
    void testWriteToXmlStream();
    void testReadFromXmlStream();

private:
    void readTextElement(const QString &tagName, const QString &elementText);
    void readString(const QString &string);
    QString patternForTag(const QString &tagname, const QString &data);
    Symbol *m_symbol;
};

#endif

