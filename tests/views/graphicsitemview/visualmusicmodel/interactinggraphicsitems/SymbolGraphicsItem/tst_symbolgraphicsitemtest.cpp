/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "testgraphicbuilder.h"
#include <src/views/graphicsitemview/visualmusicmodel/interactinggraphicsitems/symbolgraphicsitem.h>

class SymbolGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    SymbolGraphicsItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testGraphicsItemType();
    void testSetGetGraphicBuilder();

private:
    SymbolGraphicsItem *m_symbolGraphicsItem;
};

SymbolGraphicsItemTest::SymbolGraphicsItemTest()
    : m_symbolGraphicsItem(0)
{
}

void SymbolGraphicsItemTest::init()
{
    m_symbolGraphicsItem = new SymbolGraphicsItem;
}

void SymbolGraphicsItemTest::cleanup()
{
    delete m_symbolGraphicsItem;
}

void SymbolGraphicsItemTest::testGraphicsItemType()
{
    QVERIFY2(m_symbolGraphicsItem->type() == SymbolGraphicsItem::Type,
             "Wrong graphics item type returned");
}

void SymbolGraphicsItemTest::testSetGetGraphicBuilder()
{
    SymbolGraphicBuilder *builder = new TestGraphicBuilder;
    m_symbolGraphicsItem->setGraphicBuilder(builder);

    QVERIFY2(m_symbolGraphicsItem->graphicBuilder() == builder,
              "Failed setting/getting graphic builder");
}

QTEST_MAIN(SymbolGraphicsItemTest)

#include "tst_symbolgraphicsitemtest.moc"
