/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "musicitem.h"

class MusicItemTest : public QObject
{
    Q_OBJECT
    
public:
    MusicItemTest();
    ~MusicItemTest() { delete m_parent; }
    
private slots:
    void testConstructorAndGetters();
    void testChildAt();
    void testRowOfChild();

private:
    MusicItem *m_parent;
    MusicItem *m_child1;
    MusicItem *m_child2;
    MusicItem *m_child3;
    void resetData();
};

MusicItemTest::MusicItemTest() : m_parent(0), m_child1(0), m_child2(0), m_child3(0)
{
    resetData();
}

void MusicItemTest::testConstructorAndGetters()
{
    resetData();
    QVERIFY2(m_parent == m_child1->parent(), "Parentitem not set in constructor, or parent-getter fail");
    m_child1->setName("Hello");
    QVERIFY2(m_child1->name() == "Hello", "Failed setting and getting name");
}

void MusicItemTest::testChildAt()
{
    resetData();
    QVERIFY2(m_parent->childAt(1) == m_child2, "Failed to get the childitem at row");
}

void MusicItemTest::testRowOfChild()
{
    resetData();
    QVERIFY2(m_parent->rowOfChild(m_child2) == 1, "Failed to get the correct row of the child");
}

void MusicItemTest::resetData()
{
    delete m_parent;

    m_parent = new MusicItem();
    m_child1 = new MusicItem(m_parent);
    m_child2 = new MusicItem(m_parent);
    m_child3 = new MusicItem(m_parent);
}

QTEST_APPLESS_MAIN(MusicItemTest)

#include "tst_musicitemtest.moc"
