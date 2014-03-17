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
#include <QGraphicsLinearLayout>
#include <src/views/graphicsitemview/visualmusicmodel/interactinggraphicsitems/staffgraphicsitem.h>

#include <QDebug>

class StaffGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    StaffGraphicsItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testType();
    void testDefaultStaffType();
    void testMeasureLayout();
    void testSetGetStaffType();
    void testSetGetStaffLineHeight();
    void testSetGetPenWidth();
    void testSizePolicy();
    void testStandardStaffSize();
    void testStandardStaffBoundingRect();
    void testInsertChildItemImplementation();
    void testMeasureCount();

private:
    StaffGraphicsItem *m_staffGraphicsItem;
};

StaffGraphicsItemTest::StaffGraphicsItemTest()
    : m_staffGraphicsItem(0)
{
}

void StaffGraphicsItemTest::init()
{
    m_staffGraphicsItem = new StaffGraphicsItem();
}

void StaffGraphicsItemTest::cleanup()
{
    delete m_staffGraphicsItem;
}

void StaffGraphicsItemTest::testType()
{
    QVERIFY2(m_staffGraphicsItem->type() == StaffGraphicsItem::Type,
             "Wrong type for staff graphics item");
}

void StaffGraphicsItemTest::testDefaultStaffType()
{
    QVERIFY2(m_staffGraphicsItem->staffType() == StaffType::None,
             "Wrong default staff type");
}

void StaffGraphicsItemTest::testMeasureLayout()
{
    QVERIFY2(m_staffGraphicsItem->layout() != 0, "No layout set");
    QVERIFY2(m_staffGraphicsItem->m_measureLayout != 0, "Measure layout wasn't initialized");
    QVERIFY2(m_staffGraphicsItem->m_measureLayout->spacing() == 0,
             "Spacing is not 0");

    qreal top, right, bottom, left;
    m_staffGraphicsItem->m_measureLayout->getContentsMargins(&left, &top, &right, &bottom);
    QVERIFY2(top == 0, "Contents margin is wrong");
    QVERIFY2(right == 0, "Contents margin is wrong");
    QVERIFY2(bottom == 0, "Contents margin is wrong");
    QVERIFY2(left == 0, "Contents margin is wrong");
}

void StaffGraphicsItemTest::testSetGetStaffType()
{
    StaffType testType = StaffType::Standard;
    m_staffGraphicsItem->setStaffType(testType);

    QVERIFY2(m_staffGraphicsItem->staffType() == testType,
             "Failed setting/getting staff type");
}

void StaffGraphicsItemTest::testSetGetStaffLineHeight()
{
    int testLineHeight = 20;
    QVERIFY2(m_staffGraphicsItem->staffLineHeight() == 0,
             "Default line height is not 0");
    m_staffGraphicsItem->setStaffLineHeight(testLineHeight);
    QVERIFY2(m_staffGraphicsItem->staffLineHeight() == testLineHeight,
             "Failed getting line height");

    m_staffGraphicsItem->setStaffLineHeight(0);
    QVERIFY2(m_staffGraphicsItem->staffLineHeight() != 0,
             "Line height can't be 0");

    m_staffGraphicsItem->setStaffLineHeight(-12);
    QVERIFY2(m_staffGraphicsItem->staffLineHeight() != -12,
             "Line height can't be less than 0");
}

void StaffGraphicsItemTest::testSetGetPenWidth()
{
    int testLineWidth = 2;
    QVERIFY2(m_staffGraphicsItem->penWidth() == 1,
             "Wrong default line width");

    m_staffGraphicsItem->setPenWidth(testLineWidth);
    QVERIFY2(m_staffGraphicsItem->penWidth() == testLineWidth,
             "Failed setting line width");

    m_staffGraphicsItem->setPenWidth(0);
    QVERIFY2(m_staffGraphicsItem->penWidth() != 0,
             "Line height can't be 0");

    m_staffGraphicsItem->setPenWidth(-12);
    QVERIFY2(m_staffGraphicsItem->penWidth() != -12,
             "Line height can't be less than 0");
}

void StaffGraphicsItemTest::testSizePolicy()
{
    QVERIFY2(m_staffGraphicsItem->sizePolicy().verticalPolicy() == QSizePolicy::Fixed,
             "Wrong vertical size policy");
    QVERIFY2(m_staffGraphicsItem->sizePolicy().horizontalPolicy() == QSizePolicy::MinimumExpanding,
             "Wrong horizontal size policy");
}

void StaffGraphicsItemTest::testStandardStaffSize()
{
    int testLineHeight = 16;
    m_staffGraphicsItem->setStaffLineHeight(testLineHeight);
    m_staffGraphicsItem->setStaffType(StaffType::Standard);

    qreal maximumHeight = m_staffGraphicsItem->maximumHeight();
    qreal minimumHeight = m_staffGraphicsItem->minimumHeight();
    QVERIFY2(maximumHeight == minimumHeight, "No fixed size set");
    QVERIFY2(maximumHeight == 4 * testLineHeight,
             "Wrong height returned");

    // Test size changing after setting line height
    testLineHeight += 2;
    m_staffGraphicsItem->setStaffLineHeight(testLineHeight);
    maximumHeight = m_staffGraphicsItem->maximumHeight();
    minimumHeight = m_staffGraphicsItem->minimumHeight();
    QVERIFY2(maximumHeight == 4 * testLineHeight,
             "size hint was not modified after setting line height");
}

void StaffGraphicsItemTest::testStandardStaffBoundingRect()
{
    qreal testLineHeight = 26;
    qreal testLineWidth = 4;
    int testItemWidth = 50;
    m_staffGraphicsItem->setStaffLineHeight(testLineHeight);
    m_staffGraphicsItem->setPenWidth(testLineWidth);
    m_staffGraphicsItem->setStaffType(StaffType::Standard);
    m_staffGraphicsItem->setGeometry(0, 0, testItemWidth, m_staffGraphicsItem->maximumHeight());
    qreal testItemHeight = m_staffGraphicsItem->maximumHeight();

    QRectF boundingRect = m_staffGraphicsItem->boundingRect();
    qreal halfLineWidth = testLineWidth/2;
    QVERIFY2(boundingRect.left() == -(halfLineWidth),
             "Wrong left side of bounding rect");
    QVERIFY2(boundingRect.top() == -(halfLineWidth),
             "Wrong top side of bounding rect");
    QVERIFY2(boundingRect.right() == testItemWidth + halfLineWidth,
             "Wrong right side of bounding rect");
    QVERIFY2(boundingRect.bottom() == testItemHeight + halfLineWidth,
             "Wrong bottom side of bounding rect");
}

void StaffGraphicsItemTest::testInsertChildItemImplementation()
{
    InteractingGraphicsItem *testInteractingItem1 = new InteractingGraphicsItem;
    InteractingGraphicsItem *testInteractingItem2 = new InteractingGraphicsItem;
    InteractingGraphicsItem *testInteractingItem3 = new InteractingGraphicsItem;

    m_staffGraphicsItem->insertChildItem(0, testInteractingItem1);
    QVERIFY2(m_staffGraphicsItem->m_measureLayout->count(),
             "No child item was inserted");

    m_staffGraphicsItem->insertChildItem(1, testInteractingItem3);
    m_staffGraphicsItem->insertChildItem(1, testInteractingItem2);

    QVERIFY2(m_staffGraphicsItem->m_measureLayout->count() == 3,
             "Not all items were inserted");
    QVERIFY2(m_staffGraphicsItem->m_measureLayout->itemAt(1) == testInteractingItem2,
             "Item was inserted in wrong position");

    delete testInteractingItem1;
    delete testInteractingItem2;
    delete testInteractingItem3;
}

void StaffGraphicsItemTest::testMeasureCount()
{
    InteractingGraphicsItem *testInteractingItem1 = new InteractingGraphicsItem;
    InteractingGraphicsItem *testInteractingItem2 = new InteractingGraphicsItem;

    QVERIFY2(m_staffGraphicsItem->measureCount() == 0,
             "No empty measure count");

    m_staffGraphicsItem->insertChildItem(0, testInteractingItem1);
    m_staffGraphicsItem->insertChildItem(1, testInteractingItem2);

    QVERIFY2(m_staffGraphicsItem->measureCount() == 2,
             "Wrong measure count");

    delete testInteractingItem1;
    delete testInteractingItem2;
}

QTEST_MAIN(StaffGraphicsItemTest)

#include "tst_staffgraphicsitemtest.moc"
