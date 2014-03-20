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
#include <common/itemdataroles.h>
#include <app/commonpluginmanager.h>
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
    void testSetGetLineHeight();
    void testGraphicsDataStaffLineHeight();

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

void SymbolGraphicsItemTest::testSetGetLineHeight()
{
    QVERIFY2(m_symbolGraphicsItem->staffLineHeight() == 0, "Wrong default line height");
    m_symbolGraphicsItem->setStaffLineHeight(20);
    QVERIFY2(m_symbolGraphicsItem->staffLineHeight() == 0, "Line height was set despite no item type"
                                                      " data and plugin manager was set");
    PluginManager pluginManager(new CommonPluginManager);
    SymbolGraphicBuilder *graphicBuilder = pluginManager->symbolGraphicBuilderForType(LP::MelodyNote);
    QVERIFY2(graphicBuilder != 0, "A valid graphic builder is needed for next tests");

    m_symbolGraphicsItem->setPluginManager(pluginManager);
    m_symbolGraphicsItem->setData(LP::MelodyNote, LP::SymbolType);
    Q_ASSERT(!m_symbolGraphicsItem->m_graphicBuilder.isNull());

    int testLineHeight = 30;
    m_symbolGraphicsItem->setStaffLineHeight(testLineHeight);
    QVERIFY2(m_symbolGraphicsItem->staffLineHeight() == testLineHeight,
             "Failed setting/getting line height");
}

void SymbolGraphicsItemTest::testGraphicsDataStaffLineHeight()
{
    int testData(45);
    int testDataRole(LP::View::StaffLineHeight);
    PluginManager pluginManager(new CommonPluginManager);
    SymbolGraphicBuilder *graphicBuilder = pluginManager->symbolGraphicBuilderForType(LP::MelodyNote);
    QVERIFY2(graphicBuilder != 0, "A valid graphic builder is needed for next tests");
    m_symbolGraphicsItem->setPluginManager(pluginManager);
    m_symbolGraphicsItem->setData(LP::MelodyNote, LP::SymbolType);
    Q_ASSERT(!m_symbolGraphicsItem->m_graphicBuilder.isNull());

    m_symbolGraphicsItem->setGraphicsData(testDataRole, testData);
    QVERIFY2(m_symbolGraphicsItem->graphicsData(testDataRole).toInt() == testData,
             "Parent implementation wasn't called in setGraphicsData implementation");

    QVERIFY2(m_symbolGraphicsItem->m_graphicBuilder->staffLineHeight() == testData,
             "Staff line height wasn't set on graphic builder");
}

QTEST_MAIN(SymbolGraphicsItemTest)

#include "tst_symbolgraphicsitemtest.moc"
