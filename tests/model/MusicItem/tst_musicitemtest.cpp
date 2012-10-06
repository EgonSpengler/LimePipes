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
#include <rootitem.h>
#include <score.h>
#include <tune.h>
#include <symbol.h>

#include <testmusicitem.h>

class MusicItemTest : public QObject
{
    Q_OBJECT
    
public:
    MusicItemTest()
        : m_parent(0),
          m_child1(0),
          m_child2(0),
          m_child3(0) {}

private slots:
    void init();
    void cleanup();
    void testCreateMusicItem();
    void testInitData();
    void testDataPolicyForRole();
    void testReadData();
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
    void testOkToInsertChild();

private:
    MusicItem *m_parent;
    MusicItem *m_child1;
    MusicItem *m_child2;
    MusicItem *m_child3;

    MusicItem *musicItemFactory(int type) {
        switch(type)
        {
        case MusicItem::NoItemType:
            return new TestMusicItem();
        case MusicItem::RootItemType:
            return new RootItem();
        case MusicItem::ScoreType:
            return new Score();
        case MusicItem::TuneType:
            return new Tune();
        case MusicItem::SymbolType:
            return new Symbol();
        default:
            return new TestMusicItem();
        }
    }
};

void MusicItemTest::init()
{
    m_parent = musicItemFactory(MusicItem::RootItemType);
    m_child1 = musicItemFactory(m_parent->childType());
    m_child2 = musicItemFactory(m_parent->childType());
    m_child3 = musicItemFactory(m_parent->childType());
    m_parent->addChild(m_child1);
    m_parent->addChild(m_child2);
    m_parent->addChild(m_child3);
}

void MusicItemTest::cleanup()
{
    delete m_parent;
}

void MusicItemTest::testCreateMusicItem()
{
    QVERIFY2(m_parent == m_child1->parent(), "Parent item not set in constructor, or parent-getter fail");
}

void MusicItemTest::testInitData()
{
    MusicItem *item = new TestMusicItem();
    QVERIFY2(item->dataPolicyForRole(TestMusicItem::initDataRole).isWritable() == false, "Data Role must be read only for this test");
    QVERIFY2(item->data(TestMusicItem::initDataRole) == TestMusicItem::dataForInitDataRole, "Failed init data in MusicItem subclass");
    delete item;
}

void MusicItemTest::testDataPolicyForRole()
{
    MusicItem *m_testItem = new TestMusicItem();

    m_testItem = new TestMusicItem();
    DataPolicy defaultPolicy = m_testItem->dataPolicyForRole(TestMusicItem::defaultDataRole);
    QVERIFY2(defaultPolicy.isReadable() == true, "data policy is not readable");
    QVERIFY2(defaultPolicy.isWritable() == true, "data policy is not writable");

    delete m_testItem;
}

void MusicItemTest::testReadData()
{
    MusicItem *item = new TestMusicItem();
    QVERIFY2(item->data(TestMusicItem::readDataReimplementationRole) == TestMusicItem::dataForReadDataReimplementation, "read data was not called");
    delete item;
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
    MusicItem *newChild = musicItemFactory(m_parent->childType());
    newChild->setData("newChild", Qt::DisplayRole);
    QVERIFY2(m_parent->insertChild(1, newChild), "insertChild returnded false");
    QVERIFY2(m_parent->childAt(1)->data(Qt::DisplayRole) == "newChild", "Failed to insert child");

    // Insert Item thats not the correct child item
    int childCountBefore = m_parent->childCount();
    MusicItem::Type wrongChildType = MusicItem::SymbolType;
    QVERIFY2(wrongChildType != m_parent->childType(), "Choose another item type for the following test!");

    QVERIFY2(m_parent->insertChild(1, musicItemFactory(wrongChildType)) == false, "insertChild returned true despite wrong child type");
    QVERIFY2(childCountBefore == m_parent->childCount(), "A child item with the wrong type was inserted");
}

void MusicItemTest::testAddChild()
{
    int childCountBefore = m_parent->childCount();
    MusicItem *newChild = musicItemFactory(m_parent->childType());
    newChild->setData("newChild", Qt::DisplayRole);
    QVERIFY2(m_parent->addChild(newChild), "addChild returned false");
    QVERIFY2(m_parent->childAt(childCountBefore)->data(Qt::DisplayRole) == "newChild", "Failed to add child");

    // Add Item thats not the correct child item
    childCountBefore = m_parent->childCount();
    MusicItem::Type wrongChildType = MusicItem::SymbolType;
    QVERIFY2(wrongChildType != m_parent->childType(), "Choose another ItemType type for the following test!");

    QVERIFY2(m_parent->addChild(musicItemFactory(wrongChildType)) == false, "addChild returned true despite wrong child type");
    QVERIFY2(childCountBefore == m_parent->childCount(), "A child item with the wrong type was added");
}

void MusicItemTest::testInsertNoItemTypeChild()
{
    // MusicItems with NoItemType as childType should not be able to add/insert child items

    // itemtype must be one with NoItem as childType
    MusicItem::Type itemType = MusicItem::SymbolType;
    MusicItem *itemNoChild = musicItemFactory(itemType);
    QVERIFY2(itemNoChild->childType() == MusicItem::NoItemType, "For the following tests we need a MusicItem with NoItem type as childType");

    MusicItem *item = musicItemFactory(itemType);

    // Tests with insertChild
    MusicItem *childItem = musicItemFactory(item->childType());
    QVERIFY2(item->insertChild(0, childItem) == false, "Failed, inserting items with NoItem type returned true");
    QVERIFY2(item != childItem->parent(), "Failed, items with NoItem type can be inserted as children");

    // Tests with addChild
    MusicItem *childItem2 = musicItemFactory(item->childType());
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
    QVERIFY2(m_parent->type() == MusicItem::RootItemType, "type() in MusicItem doesn't return NoItem as type");
}

void MusicItemTest::testChildType()
{
    // A MusicItem is used as the root item. So the child type should be ScoreType
    QVERIFY2(m_parent->childType() == MusicItem::ScoreType, "childType() in MusicItem doesn't return ScoreType");
}

void MusicItemTest::testOkToInsertChild()
{
    MusicItem *item = new TestMusicItem();
    QVERIFY2(m_parent->okToInsertChild(item) == true, "Default implementation should return true");
    delete item;
}

QTEST_APPLESS_MAIN(MusicItemTest)

#include "tst_musicitemtest.moc"
