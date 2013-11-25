/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <views/graphicsitemview/visualmusicmodel/visualsymbol.h>

class VisualSymbolTest : public QObject
{
    Q_OBJECT

public:
    VisualSymbolTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testGraphicalType();

private:
    VisualSymbol *m_visualSymbol;
};

VisualSymbolTest::VisualSymbolTest()
    : m_visualSymbol(0)
{
}

void VisualSymbolTest::init()
{
    m_visualSymbol = new VisualSymbol();
}

void VisualSymbolTest::cleanup()
{
    delete m_visualSymbol;
}

void VisualSymbolTest::testType()
{
    QVERIFY2(m_visualSymbol->itemType() == VisualItem::VisualSymbolItem,
             "Visual symbol returned wrong type");
}

void VisualSymbolTest::testGraphicalType()
{
    QVERIFY2(m_visualSymbol->graphicalType() == VisualItem::GraphicalInlineType,
             "Returned wrong graphical type");
}

QTEST_APPLESS_MAIN(VisualSymbolTest)

#include "tst_visualsymboltest.moc"
