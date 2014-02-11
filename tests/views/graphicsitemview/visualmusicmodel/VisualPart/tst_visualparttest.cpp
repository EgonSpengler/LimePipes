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
#include <QSignalSpy>
#include <common/itemdataroles.h>
#include <views/graphicsitemview/visualmusicmodel/visualpart.h>
#include <views/graphicsitemview/visualmusicmodel/interactinggraphicsitems/staffgraphicsitem.h>

class VisualPartTest : public QObject
{
    Q_OBJECT

public:
    VisualPartTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testSetGetRepeat();
    void testSetDataRepeat();
    void testSetGetStaffType();
    void testSetDataStaffType();
    void testDefaultStaffCount();
    void testAppendStaffItem();
    void testRemoveLastStaffItem();
    void testSetStaffTypeOnStaffItem();
    void testInsertChildItemImplementation();

private:
    VisualPart *m_visualPart;
};

VisualPartTest::VisualPartTest()
{
}

void VisualPartTest::init()
{
    m_visualPart = new VisualPart;
}

void VisualPartTest::cleanup()
{
    delete m_visualPart;
}

void VisualPartTest::testConstructor()
{
    QVERIFY2(m_visualPart->itemType() == VisualItem::VisualPartItem,
             "Wrong item type returned");
    QVERIFY2(m_visualPart->graphicalType() == VisualItem::GraphicalRowType,
             "Wrong graphical type returned");
}

void VisualPartTest::testSetGetRepeat()
{
    QVERIFY2(m_visualPart->repeat() == false, "Default repeat is not false");

    m_visualPart->setRepeat(true);

    QVERIFY2(m_visualPart->repeat() == true, "Failed setting repeat");
}

void VisualPartTest::testSetDataRepeat()
{
    m_visualPart->setData(true, LP::PartRepeat);
    QVERIFY2(m_visualPart->repeat() == true,
             "Failed setting repeat through setData");
}

void VisualPartTest::testSetGetStaffType()
{
    QVERIFY2(m_visualPart->staffType() == StaffType::None, "Default staff type is wrong");

    m_visualPart->setStaffType(StaffType::Standard);

    QVERIFY2(m_visualPart->staffType() == StaffType::Standard, "Failed setting staff type");
}

void VisualPartTest::testSetDataStaffType()
{
    m_visualPart->setData(QVariant::fromValue<StaffType>(StaffType::Standard), LP::PartStaffType);
    QVERIFY2(m_visualPart->staffType() == StaffType::Standard,
             "Failed setting staff type through setData");
}

void VisualPartTest::testDefaultStaffCount()
{
    int defaultCount = 1;
    QVERIFY2(m_visualPart->staffCount() == defaultCount,
             "Wrong default staff count");
    QVERIFY2(m_visualPart->rowCount() == defaultCount,
             "Wrong default row graphics count");
}

void VisualPartTest::testAppendStaffItem()
{
    QSignalSpy spy(m_visualPart, SIGNAL(rowSequenceChanged()));
    m_visualPart->appendStaff();
    QVERIFY2(m_visualPart->staffCount() == 2, "No staff was appended");
    QVERIFY2(spy.count() == 1, "Row sequence changed signal wasn't emitted");
}

void VisualPartTest::testRemoveLastStaffItem()
{
    m_visualPart->removeLastStaff();
    QVERIFY2(m_visualPart->staffCount() > 0, "Last staff was removed, no staff left...");
    m_visualPart->appendStaff();
    Q_ASSERT(m_visualPart->staffCount() == 2);

    QSignalSpy spy(m_visualPart, SIGNAL(rowSequenceChanged()));
    m_visualPart->removeLastStaff();
    QVERIFY2(m_visualPart->staffCount() == 1, "Last staff wasn't removed");
    QVERIFY2(m_visualPart->rowCount() == 1, "Last row graphics item wasn't removed");
    QVERIFY2(spy.count() == 1, "Row sequence changed signal wasn't emitted");
}

void VisualPartTest::testSetStaffTypeOnStaffItem()
{
    StaffType testStaffType = StaffType::Standard;
    Q_ASSERT(m_visualPart->staffType() != testStaffType);
    m_visualPart->setStaffType(testStaffType);
    foreach (StaffGraphicsItem *staff, m_visualPart->m_staffItems) {
        QVERIFY2(staff->staffType() == m_visualPart->staffType(),
                 "Staff has not the right staff type set");
    }
}

void VisualPartTest::testInsertChildItemImplementation()
{
    VisualItem *testVisualItem = new VisualItem;
    testVisualItem->setGraphicalType(VisualItem::GraphicalInlineType);
    InteractingGraphicsItem *testMeasureItem = new InteractingGraphicsItem;
    testVisualItem->setInlineGraphic(testMeasureItem);

    Q_ASSERT(testVisualItem->inlineGraphic() != 0);
    Q_ASSERT(m_visualPart->m_staffItems.count());

    m_visualPart->insertChildItem(0, testVisualItem);

    QVERIFY2(m_visualPart->m_staffItems.at(0)->measureCount() == 1,
             "Measure wasn't inserted");
}

QTEST_MAIN(VisualPartTest)

#include "tst_visualparttest.moc"
