/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <views/graphicsitemview/visualmusicmodel/visualitem.h>
#include <views/graphicsitemview/visualmusicmodel/interactinggraphicsitems/interactinggraphicsitem.h>
#include <QtTest/QtTest>

class VisualItemTest : public QObject
{
    Q_OBJECT
    
public:
    VisualItemTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testInitialItemType();
    void testInitialGraphicalType();
    void testDefaultInlineGraphic();
    void testDefaultRowGraphics();
    void testSetGetItemType();
    void testSetGetGraphicalType();
    void testInlineGraphic();

private:
    VisualItem *m_visualItem;
};

VisualItemTest::VisualItemTest()
    : m_visualItem(0)
{
}

void VisualItemTest::init()
{
    m_visualItem = new VisualItem();
}

void VisualItemTest::cleanup()
{
    delete m_visualItem;
}

void VisualItemTest::testConstructor()
{
    delete m_visualItem;
    m_visualItem = new VisualItem(VisualItem::VisualScoreItem);

    QVERIFY2(m_visualItem->itemType() == VisualItem::VisualScoreItem, "Item type wasn't set in constructor");
    QVERIFY2(m_visualItem->graphicalType() == VisualItem::NoGraphicalType,
             "Graphical type is not default in constructor without graphical type parameter");

    delete m_visualItem;
    m_visualItem = new VisualItem(VisualItem::VisualMeasureItem, VisualItem::GraphicalRowType);
    QVERIFY2(m_visualItem->itemType() == VisualItem::VisualMeasureItem, "Item type wasn't set in constructor");
    QVERIFY2(m_visualItem->graphicalType() == VisualItem::GraphicalRowType,
             "Graphical type wasn't set in constructor");
}

void VisualItemTest::testInitialItemType()
{
    QVERIFY2(m_visualItem->itemType() == VisualItem::NoVisualItem, "Wrong initial itemtype");
}

void VisualItemTest::testInitialGraphicalType()
{
    QVERIFY2(m_visualItem->graphicalType() == VisualItem::NoGraphicalType, "Wrong initial graphical type");
}

void VisualItemTest::testDefaultInlineGraphic()
{
    QVERIFY2(m_visualItem->inlineGraphic() == 0, "Default inline graphic is not 0");
}

void VisualItemTest::testDefaultRowGraphics()
{
    QVERIFY2(m_visualItem->rowGraphics().isEmpty(), "Default row graphics is not empty");
}

void VisualItemTest::testSetGetItemType()
{
    m_visualItem->setItemType(VisualItem::VisualMeasureItem);
    QVERIFY2(m_visualItem->itemType() == VisualItem::VisualMeasureItem,
             "Failed setting item type and getting it back");
}

void VisualItemTest::testSetGetGraphicalType()
{
    m_visualItem->setGraphicalType(VisualItem::GraphicalRowType);
    QVERIFY2(m_visualItem->graphicalType() == VisualItem::GraphicalRowType,
             "Failed setting graphical type and getting it back");
}

void VisualItemTest::testInlineGraphic()
{
    InteractingGraphicsItem *graphicsItem  = new InteractingGraphicsItem();
    InteractingGraphicsItem *graphicsItem2 = new InteractingGraphicsItem();
    m_visualItem->setGraphicalType(VisualItem::GraphicalInlineType);

    QVERIFY2(m_visualItem->inlineGraphic() == 0, "Inline graphic is already set");

    // Set item
    m_visualItem->setInlineGraphic(graphicsItem);
    QVERIFY2(m_visualItem->inlineGraphic() == graphicsItem, "Failed setting inline graphic and getting it back");

    // Set new item
    m_visualItem->setInlineGraphic(graphicsItem2);
    QVERIFY2(m_visualItem->inlineGraphic() == graphicsItem2, "Failed setting new inline graphic and getting it back");

    // Set 0 item
    m_visualItem->setInlineGraphic(0);
    QVERIFY2(m_visualItem->inlineGraphic() == graphicsItem2, "Failure, setting 0 pointer was successful");

    // Test on row graphic, should always return 0 for inline graphic
    delete m_visualItem;
    m_visualItem = new VisualItem();
    m_visualItem->setGraphicalType(VisualItem::GraphicalRowType);

    Q_ASSERT(m_visualItem->inlineGraphic() == 0);
    m_visualItem->setInlineGraphic(graphicsItem);
    QVERIFY2(m_visualItem->inlineGraphic() == 0, "Failure, setting inline graphic in graphical row type was successful");

    // Test on no graphical type should also return 0 for inline graphic
    m_visualItem->setGraphicalType(VisualItem::NoGraphicalType);
    Q_ASSERT(m_visualItem->inlineGraphic() == 0);
    m_visualItem->setInlineGraphic(graphicsItem);
    QVERIFY2(m_visualItem->inlineGraphic() == 0, "Failure, setting inline graphic in no graphical item type was successful");

}

QTEST_APPLESS_MAIN(VisualItemTest)

#include "tst_visualitemtest.moc"
