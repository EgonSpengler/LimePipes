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
#include <src/views/graphicsitemview/visualmusicmodel/interactinggraphicsitems/staffgraphicsitem.h>

class StaffGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    StaffGraphicsItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultStaffType();
    void testSetGetStaffType();

private:
    StaffGraphicsItem *m_graphicsItem;
};

StaffGraphicsItemTest::StaffGraphicsItemTest()
    : m_graphicsItem(0)
{
}

void StaffGraphicsItemTest::init()
{
    m_graphicsItem = new StaffGraphicsItem();
}

void StaffGraphicsItemTest::cleanup()
{
    delete m_graphicsItem;
}

void StaffGraphicsItemTest::testDefaultStaffType()
{
    QVERIFY2(m_graphicsItem->staffType() == StaffType::None,
             "Wrong default staff type");
}

void StaffGraphicsItemTest::testSetGetStaffType()
{
    StaffType testType = StaffType::Standard;
    m_graphicsItem->setStaffType(testType);

    QVERIFY2(m_graphicsItem->staffType() == testType,
             "Failed setting/getting staff type");
}

QTEST_MAIN(StaffGraphicsItemTest)

#include "tst_staffgraphicsitemtest.moc"
