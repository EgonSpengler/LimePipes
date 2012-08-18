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

class MusicItemTest : public QObject
{
    Q_OBJECT
    
public:
    MusicItemTest() : m_parent(0), m_child1(0), m_child2(0), m_child3(0) {}
    
private slots:
    void init();
    void cleanup();
    void testCreateMusicItem();
    void testSetName();
    void testChildAt();
    void testRowOfChild();
    void testChildCount();
    void testHasChildren();
    void testChildrenGetter();
    void testInsertChild();
    void testAddChild();
    void testSwapChildren();
    void testType();
    void testParentType();
    void testData();

private:
    MusicItem *m_parent;
    MusicItem *m_child1;
    MusicItem *m_child2;
    MusicItem *m_child3;
};

void MusicItemTest::init()
{
    m_parent = new MusicItem();
    m_child1 = new MusicItem(m_parent);
    m_child2 = new MusicItem(m_parent);
    m_child3 = new MusicItem(m_parent);
}

void MusicItemTest::cleanup()
{
    delete m_parent;
}

void MusicItemTest::testCreateMusicItem()
{
    QVERIFY2(m_parent == m_child1->parent(), "Parentitem not set in constructor, or parent-getter fail");
}

void MusicItemTest::testSetName()
{
    m_child1->setName("Hello");
    QVERIFY2(m_child1->name() == "Hello", "Failed setting and getting name");
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
    MusicItem *newChild = new MusicItem();
    newChild->setName("newChild");
    m_parent->insertChild(1, newChild);
    QVERIFY2(m_parent->childAt(1)->name() == "newChild", "Failed to insert child");
}

void MusicItemTest::testAddChild()
{
    int childCountBefore = m_parent->childCount();
    MusicItem *newChild = new MusicItem();
    newChild->setName("newChild");
    m_parent->addChild(newChild);
    QVERIFY2(m_parent->childAt(childCountBefore)->name() == "newChild", "Failed to add child");
}

void MusicItemTest::testSwapChildren()
{
    m_child1->setName("child1");
    m_child2->setName("child2");
    m_parent->swapChildren(0, 1);
    QVERIFY2(m_parent->childAt(0)->name() == "child2", "Failed to swap children");
    QVERIFY2(m_parent->childAt(1)->name() == "child1", "Failed to swap children");
}

void MusicItemTest::testType()
{
    QVERIFY2(m_parent->type() == NoItemType, "type() in MusicItem doesn't return NoItemType");
}

void MusicItemTest::testParentType()
{
    QVERIFY2(m_parent->parentType() == NoItemType, "parentType() in MusicItem doesn't return NoItemType");
}

void MusicItemTest::testData()
{
    m_parent->setName("the_parent_item");
    QVERIFY2(m_parent->data(Qt::DisplayRole) == m_parent->name(), "DisplayRole should return the itemname");
}

QTEST_APPLESS_MAIN(MusicItemTest)

#include "tst_musicitemtest.moc"
