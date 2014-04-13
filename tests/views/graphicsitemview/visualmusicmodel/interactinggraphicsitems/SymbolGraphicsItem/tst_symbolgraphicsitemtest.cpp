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
#include <QSignalSpy>
#include <common/itemdataroles.h>
#include <app/commonpluginmanager.h>
#include <testsymbolgraphicbuilder.h>
#include <src/views/graphicsitemview/visualmusicmodel/interactinggraphicsitems/symbolgraphicsitem.h>

Q_IMPORT_PLUGIN(IntegratedSymbols)

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
    void testSetGetPluginManager();
    void testSetDataItemType();
    void testSetDataOfGraphicBuilder();

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
    SymbolGraphicBuilder *builder = new TestSymbolGraphicBuilder;
    m_symbolGraphicsItem->setGraphicBuilder(builder);

    QVERIFY2(m_symbolGraphicsItem->graphicBuilder() == builder,
             "Failed setting/getting graphic builder");
}

void SymbolGraphicsItemTest::testSetGetPluginManager()
{
    PluginManager pluginManager(new CommonPluginManager);
    m_symbolGraphicsItem->setPluginManager(pluginManager);
    QVERIFY2(m_symbolGraphicsItem->pluginManger() == pluginManager,
             "Failed setting/getting plugin manager");
}

void SymbolGraphicsItemTest::testSetDataItemType()
{
    PluginManager pluginManager(new CommonPluginManager);
    SymbolGraphicBuilder *graphicBuilder = pluginManager->symbolGraphicBuilderForType(LP::MelodyNote);
    QVERIFY2(graphicBuilder != 0, "A valid graphic builder is needed for next tests");

    m_symbolGraphicsItem->setPluginManager(pluginManager);
    m_symbolGraphicsItem->setData(LP::MelodyNote, LP::SymbolType);

    QVERIFY2(!m_symbolGraphicsItem->m_graphicBuilder.isNull(),
             "Symbol graphic builder wasn't set");
}

void SymbolGraphicsItemTest::testSetDataOfGraphicBuilder()
{
    int testDataRole = LP::SymbolCategory;
    int testValue = 12;
    TestSymbolGraphicBuilder *graphicBuilder = new TestSymbolGraphicBuilder;
    QVector<int> builderDataRoles;
    builderDataRoles.append(testDataRole);
    graphicBuilder->setGraphicDataRoles(builderDataRoles);
    m_symbolGraphicsItem->setGraphicBuilder(graphicBuilder);
    Q_ASSERT(!m_symbolGraphicsItem->m_graphicBuilder.isNull());

    m_symbolGraphicsItem->setData(testValue, testDataRole);
    QVERIFY2(graphicBuilder->data(testDataRole).toInt() == testValue,
            "setData wasn't called on graphic builder in SymbolGraphicsItem");
}

QTEST_MAIN(SymbolGraphicsItemTest)

#include "tst_symbolgraphicsitemtest.moc"
