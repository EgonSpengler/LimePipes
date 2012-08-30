/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <musicitem.h>
#include <musicitemfactory.h>

class MusicItemTest : public QObject
{
    Q_OBJECT
    
public:
    MusicItemTest() : m_parent(0), m_child1(0), m_child2(0), m_child3(0) {}

private slots:
    void init();
    void cleanup();
    void testCreateMusicItem();
    void testSetData();
    void testChildAt();
    void testRowOfChild();
    void testChildCount();
    void testHasChildren();
    void testChildrenGetter();
    void testInsertChild();
    void testAddChild();
    void testInsertNoItemTypeChild();
    void testSwapChildren();
    void testType();
    void testChildType();
    void testData();

private:
    MusicItem *m_parent;
    MusicItem *m_child1;
    MusicItem *m_child2;
    MusicItem *m_child3;


};

void MusicItemTest::init()
{
    m_parent = MusicItemFactory::getMusicItem(MusicItem::RootItem);
    MusicItem *firstLevelItem = MusicItemFactory::getMusicItem(m_parent->childType());
    m_child1 = new MusicItem(m_parent->childType(), firstLevelItem->childType(), m_parent);
    m_child2 = new MusicItem(m_parent->childType(), firstLevelItem->childType(), m_parent);
    m_child3 = new MusicItem(m_parent->childType(), firstLevelItem->childType(), m_parent);
}

void MusicItemTest::cleanup()
{
    delete m_parent;
}

void MusicItemTest::testCreateMusicItem()
{
    QVERIFY2(m_parent == m_child1->parent(), "Parent item not set in constructor, or parent-getter fail");

    // Default MusicItem returns NoItem for type and childType
    MusicItem *item = new MusicItem();
    QVERIFY2(item->type() == MusicItem::NoItem, "Music Item returns not NoItem as type");
    QVERIFY2(item->childType() == MusicItem::NoItem, "Music Item returns not NoItem as child type");
}

void MusicItemTest::testSetData()
{
    m_parent->setData("My name", Qt::DisplayRole);
    QVERIFY2(m_parent->data(Qt::DisplayRole) == "My name", "Failed to set name throug setData()");
}

void MusicItemTest::testChildAt()
{
    QVERIFY2(m_parent->childAt(1) == m_child2, "Failed to get the childitem at row");
}

void MusicItemTest::testRowOfChild()
{
    QVERIFY2(m_parent->rowOfChild(m_child2) == 1, "Failed to get the correct row of the child");
}

void MusicItemTest::testChildCount()
{
    QVERIFY2(m_parent->childCount() == 3, "Failed to get the correct child count");
}

void MusicItemTest::testHasChildren()
{
    QVERIFY2(m_parent->hasChildren() == true, "Parent item has no children");
    QVERIFY2(m_child1->hasChildren() == false, "Child item has children");
}

void MusicItemTest::testChildrenGetter()
{
    QVERIFY2(!m_parent->children().isEmpty() , "Failed to get children from parent");
}

void MusicItemTest::testInsertChild()
{
    MusicItem *newChild = new MusicItem(m_parent->childType());
    newChild->setData("newChild", Qt::DisplayRole);
    QVERIFY2(m_parent->insertChild(1, newChild), "insertChild returnded false");
    QVERIFY2(m_parent->childAt(1)->data(Qt::DisplayRole) == "newChild", "Failed to insert child");

    // Insert Item thats not the correct child item
    int childCountBefore = m_parent->childCount();
    MusicItem::Type wrongChildType = MusicItem::Symbol;
    QVERIFY2(wrongChildType != m_parent->childType(), "Choose another item type for the following test!");

    QVERIFY2(m_parent->insertChild(1, new MusicItem(wrongChildType)) == false, "insertChild returned true despite wrong child type");
    QVERIFY2(childCountBefore == m_parent->childCount(), "A child item with the wrong type was inserted");
}

void MusicItemTest::testAddChild()
{
    int childCountBefore = m_parent->childCount();
    MusicItem *newChild = new MusicItem(m_parent->childType());
    newChild->setData("newChild", Qt::DisplayRole);
    QVERIFY2(m_parent->addChild(newChild), "addChild returned false");
    QVERIFY2(m_parent->childAt(childCountBefore)->data(Qt::DisplayRole) == "newChild", "Failed to add child");

    // Add Item thats not the correct child item
    childCountBefore = m_parent->childCount();
    MusicItem::Type wrongChildType = MusicItem::Symbol;
    QVERIFY2(wrongChildType != m_parent->childType(), "Choose another ItemType type for the following test!");

    QVERIFY2(m_parent->addChild(new MusicItem(wrongChildType)) == false, "addChild returned true despite wrong child type");
    QVERIFY2(childCountBefore == m_parent->childCount(), "A child item with the wrong type was added");
}

void MusicItemTest::testInsertNoItemTypeChild()
{
    // MusicItems with NoItemType as childType should not be able to add/insert child items

    // itemtype must be one with NoItem as childType
    MusicItem::Type itemType = MusicItem::Symbol;
    MusicItem *itemNoChild = MusicItemFactory::getMusicItem(itemType);
    QVERIFY2(itemNoChild->childType() == MusicItem::NoItem, "For the following tests we need a MusicItem with NoItem type as childType");

    MusicItem *item = new MusicItem(itemType, MusicItem::NoItem);

    // Tests with insertChild
    MusicItem *childItem = new MusicItem(item->childType(), MusicItem::NoItem);
    QVERIFY2(item->insertChild(0, childItem) == false, "Failed, inserting items with NoItem type returned true");
    QVERIFY2(item != childItem->parent(), "Failed, items with NoItem type can be inserted as children");

    // Tests with addChild
    MusicItem *childItem2 = new MusicItem(item->childType());
    QVERIFY2(item->addChild(childItem2) == false, "Failed, adding item with NoItem type returned true");
    QVERIFY2(item != childItem2->parent(), "Failed, item with NoItem type can be added as children");

    delete itemNoChild;
    delete item;

    // If tests have failed and items could be inserted as child,
    // this delete statements will end in an error
    delete childItem;
    delete childItem2;
}

void MusicItemTest::testSwapChildren()
{
    m_child1->setData("child1", Qt::DisplayRole);
    m_child2->setData("child2", Qt::DisplayRole);
    m_parent->swapChildren(0, 1);
    QVERIFY2(m_parent->childAt(0)->data(Qt::DisplayRole) == "child2", "Failed to swap children");
    QVERIFY2(m_parent->childAt(1)->data(Qt::DisplayRole) == "child1", "Failed to swap children");
}

void MusicItemTest::testType()
{
    QVERIFY2(m_parent->type() == MusicItem::RootItem, "type() in MusicItem doesn't return NoItem as type");
}

void MusicItemTest::testChildType()
{
    // A MusicItem is used as the root item. So the child type should be ScoreType
    QVERIFY2(m_parent->childType() == MusicItem::Score, "childType() in MusicItem doesn't return ScoreType");
}

void MusicItemTest::testData()
{
    m_parent->setData("the_parent_item", Qt::DisplayRole);
    QVERIFY2(m_parent->data(Qt::DisplayRole) == "the_parent_item", "DisplayRole should return the itemname");
}

QTEST_APPLESS_MAIN(MusicItemTest)

#include "tst_musicitemtest.moc"
