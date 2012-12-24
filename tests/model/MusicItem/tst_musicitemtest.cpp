/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include "tst_musicitemtest.h"

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

void MusicItemTest::testNullItemCopyConstructor()
{
    QString testTitle = "Test title";
    MusicItem *scoreItem = musicItemFactory(MusicItem::ScoreType);
    scoreItem->setData(QVariant(testTitle), LP::scoreTitle);

    NullMusicItem copyItem(*scoreItem);
    QVERIFY2(scoreItem->type() == copyItem.type(), "Items have not the same type");
    QVERIFY2(scoreItem->childType() == copyItem.childType(), "Items have not the same child type");
    QVERIFY2(scoreItem->data(LP::scoreTitle).toString() == copyItem.data(LP::scoreTitle).toString(),
             "Data wasn't copied");
}

void MusicItemTest::testInitData()
{
    MusicItem *item = new TestMusicItem();
    QVERIFY2(item->data(TestMusicItem::initDataRole) == TestMusicItem::dataForInitDataRole, "Failed init data in MusicItem subclass");
    delete item;
}

void MusicItemTest::testItemSupportsWritingOfData()
{
    MusicItem *item = new TestMusicItem();
    QVERIFY2(item->setData(QVariant(), LP::symbolName) == true, "Fail, TestMusicItem supports writing of symbol name role");
    QVERIFY2(item->setData(QVariant(), TestMusicItem::notWritableRole) == false, "Fail, role was writable.");
}

void MusicItemTest::testChildAt()
{
    QVERIFY2(m_parent->childAt(1) == m_child2, "Failed to get the childitem at row");
}

void MusicItemTest::testTakeChild()
{
    int childCountBefore = m_parent->childCount();
    MusicItem *item = m_parent->takeChild(1);
    QVERIFY2(m_parent->childCount() == childCountBefore - 1, "Failed taking child");
    QVERIFY2(item == m_child2, "Failed, took wrong child");
    QVERIFY2(item->parent() == 0, "Failed, removed item has still a parent");
}

void MusicItemTest::testParent()
{
    QVERIFY2(m_child1->parent() == m_parent, "Failed getting right parent");
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
    Q_ASSERT(newChild->type() == MusicItem::ScoreType);
    newChild->setData("newChild", LP::scoreTitle);
    QVERIFY2(m_parent->insertChild(1, newChild), "insertChild returnded false");
    QVERIFY2(m_parent->childAt(1)->data(LP::scoreTitle) == "newChild", "Failed to insert child");

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
    Q_ASSERT(newChild->type() == MusicItem::ScoreType);
    newChild->setData("newChild", LP::scoreTitle);
    QVERIFY2(m_parent->addChild(newChild), "addChild returned false");
    QVERIFY2(m_parent->childAt(childCountBefore)->data(LP::scoreTitle) == "newChild", "Failed to add child");

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
    Q_ASSERT(m_child1->type() == MusicItem::ScoreType);
    m_child1->setData("child1", LP::scoreTitle);
    m_child2->setData("child2", LP::scoreTitle);
    m_parent->swapChildren(0, 1);
    QVERIFY2(m_parent->childAt(0)->data(LP::scoreTitle) == "child2", "Failed to swap children");
    QVERIFY2(m_parent->childAt(1)->data(LP::scoreTitle) == "child1", "Failed to swap children");
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

void MusicItemTest::testSetParent()
{
    MusicItem *item = musicItemFactory(MusicItem::RootItemType);

    m_child1->setParent(item);

    QVERIFY2(m_child1->parent() == item, "Failed setting parent");
    QVERIFY2(item->rowOfChild(m_child1) == -1, "Item was added to parent");
}

void MusicItemTest::testOkToInsertChild()
{
    MusicItem *item = new TestMusicItem();
    QVERIFY2(m_parent->okToInsertChild(item, 0) == true, "Default implementation should return true");
    delete item;
}

void MusicItemTest::testAfterWritingDataCallback()
{
    TestMusicItem *item = new TestMusicItem();
    QSignalSpy spy(item, SIGNAL(afterWritingDataCalled()));
    item->setData(123, 456);
    QVERIFY2(spy.count() == 1, "afterSetData wasn't called after write data");
    item->testInitData();
    QVERIFY2(spy.count() == 2, "afterSetData wasn't called after call of initData");
}

void MusicItemTest::testBeforeWritingDataCallback()
{
    TestMusicItem *item = new TestMusicItem();
    QSignalSpy spy(item, SIGNAL(beforeWritingDataCalled()));
    item->setData(123, 456);
    QVERIFY2(spy.count() == 1, "beforeWritingData wasn't called before write data");
    item->testInitData();
    QVERIFY2(spy.count() == 2, "beforeWritingDta wasn't called before call of initData");
}

QTEST_APPLESS_MAIN(MusicItemTest)

//#include "tst_musicitemtest.moc"
