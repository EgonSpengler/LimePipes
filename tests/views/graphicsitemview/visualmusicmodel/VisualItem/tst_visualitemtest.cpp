/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <views/graphicsitemview/visualmusicmodel/visualitem.h>
#include <QtTest/QtTest>

class VisualItemTest : public QObject
{
    Q_OBJECT
    
public:
    VisualItemTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testInitialItemType();
    void testInitialGraphicalType();
    void testDefaultInlineGraphic();
    void testDefaultRowGraphics();

private:
    VisualItem *visualItem;
};

VisualItemTest::VisualItemTest()
    : visualItem(0)
{
}

void VisualItemTest::init()
{
    visualItem = new VisualItem();
}

void VisualItemTest::cleanup()
{
    delete visualItem;
}

void VisualItemTest::testInitialItemType()
{
    QVERIFY2(visualItem->itemType() == VisualItem::NoVisualItem, "Wrong initial itemtype");
}

void VisualItemTest::testInitialGraphicalType()
{
    QVERIFY2(visualItem->graphicalType() == VisualItem::NoGraphicalType, "Wrong initial graphical type");
}

void VisualItemTest::testDefaultInlineGraphic()
{
    QVERIFY2(visualItem->inlineGraphic() == 0, "Default inline graphic is not 0");
}

void VisualItemTest::testDefaultRowGraphics()
{
    QVERIFY2(visualItem->rowGraphics().isEmpty(), "Default row graphics is not empty");
}

QTEST_APPLESS_MAIN(VisualItemTest)

#include "tst_visualitemtest.moc"
