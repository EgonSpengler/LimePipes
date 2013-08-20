/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include "testabstractvisualitem.h"
#include <views/graphicsitemview/visualmusicmodel/visualrootitem.h>
#include <QtTest/QtTest>

class AbstractVisualItemTest : public QObject
{
    Q_OBJECT
    
public:
    AbstractVisualItemTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testInsertChild();
    void testChildItemAt();
    void testRemoveChildItemAt();

private:
    TestAbstractVisualItem *visualItem;
};

AbstractVisualItemTest::AbstractVisualItemTest()
    : visualItem(0)
{
}

void AbstractVisualItemTest::init()
{
    visualItem = new TestAbstractVisualItem();
}

void AbstractVisualItemTest::cleanup()
{
    delete visualItem;
}

void AbstractVisualItemTest::testInsertChild()
{
    VisualRootItem *rootItem = new VisualRootItem();
    visualItem->insertItem(0, rootItem);
    QVERIFY2(visualItem->childItemCount() == 1, "Item wasn't inserted");

    delete rootItem;
}

void AbstractVisualItemTest::testChildItemAt()
{
    VisualRootItem *rootItem1 = new VisualRootItem();
    VisualRootItem *rootItem2 = new VisualRootItem();
    visualItem->insertItem(0, rootItem1);
    visualItem->insertItem(0, rootItem2);

    QVERIFY2(visualItem->childItemAt(0) == rootItem2, "Failed getting root item on index 0");
    QVERIFY2(visualItem->childItemAt(1) == rootItem1, "Failed getting root item on index 1");

    QVERIFY2(visualItem->childItemAt(-1) == 0, "Returned child item at index -1 isn't 0");
    QVERIFY2(visualItem->childItemAt(2) == 0, "Returned child item at index 2 isn't 0");
}

void AbstractVisualItemTest::testRemoveChildItemAt()
{
    VisualRootItem *rootItem1 = new VisualRootItem();
    VisualRootItem *rootItem2 = new VisualRootItem();
    VisualRootItem *rootItem3 = new VisualRootItem();
    visualItem->insertItem(0, rootItem1);
    visualItem->insertItem(0, rootItem2);
    visualItem->insertItem(0, rootItem3);

    visualItem->removeItemAt(1);

    QVERIFY2(visualItem->childItemCount() == 2, "Child item wasn't removed");
    QVERIFY2(visualItem->childItemAt(0) == rootItem3, "First child item isn't at correct position");
    QVERIFY2(visualItem->childItemAt(1) == rootItem1, "Last child item isn't at correct position");
}

QTEST_APPLESS_MAIN(AbstractVisualItemTest)

#include "tst_abstractvisualitemtest.moc"
