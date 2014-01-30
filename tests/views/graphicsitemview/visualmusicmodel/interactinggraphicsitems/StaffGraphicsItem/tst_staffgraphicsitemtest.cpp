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
    void testSetGetLineHeight();
    void testSetGetLineWidth();
    void testSizePolicy();
    void testStandardStaffSize();
    void testStandardStaffBoundingRect();

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

void StaffGraphicsItemTest::testSetGetLineHeight()
{
    int testLineHeight = 20;
    QVERIFY2(m_graphicsItem->lineHeight() == 0,
             "Default line height is not 0");
    m_graphicsItem->setLineHeight(testLineHeight);
    QVERIFY2(m_graphicsItem->lineHeight() == testLineHeight,
             "Failed getting line height");

    m_graphicsItem->setLineHeight(0);
    QVERIFY2(m_graphicsItem->lineHeight() != 0,
             "Line height can't be 0");

    m_graphicsItem->setLineHeight(-12);
    QVERIFY2(m_graphicsItem->lineHeight() != -12,
             "Line height can't be less than 0");
}

void StaffGraphicsItemTest::testSetGetLineWidth()
{
    int testLineWidth = 2;
    QVERIFY2(m_graphicsItem->lineWidth() == 1,
             "Wrong default line width");

    m_graphicsItem->setLineWidth(testLineWidth);
    QVERIFY2(m_graphicsItem->lineWidth() == testLineWidth,
             "Failed setting line width");

    m_graphicsItem->setLineWidth(0);
    QVERIFY2(m_graphicsItem->lineWidth() != 0,
             "Line height can't be 0");

    m_graphicsItem->setLineWidth(-12);
    QVERIFY2(m_graphicsItem->lineWidth() != -12,
             "Line height can't be less than 0");
}

void StaffGraphicsItemTest::testSizePolicy()
{
    QVERIFY2(m_graphicsItem->sizePolicy().verticalPolicy() == QSizePolicy::Fixed,
             "Wrong vertical size policy");
    QVERIFY2(m_graphicsItem->sizePolicy().horizontalPolicy() == QSizePolicy::MinimumExpanding,
             "Wrong horizontal size policy");
}

void StaffGraphicsItemTest::testStandardStaffSize()
{
    int testLineHeight = 16;
    m_graphicsItem->setLineHeight(testLineHeight);
    m_graphicsItem->setStaffType(StaffType::Standard);

    qreal maximumHeight = m_graphicsItem->maximumHeight();
    qreal minimumHeight = m_graphicsItem->minimumHeight();
    QVERIFY2(maximumHeight == minimumHeight, "No fixed size set");
    QVERIFY2(maximumHeight == 4 * testLineHeight,
             "Wrong height returned");

    // Test size changing after setting line height
    testLineHeight += 2;
    m_graphicsItem->setLineHeight(testLineHeight);
    maximumHeight = m_graphicsItem->maximumHeight();
    minimumHeight = m_graphicsItem->minimumHeight();
    QVERIFY2(maximumHeight == 4 * testLineHeight,
             "size hint was not modified after setting line height");
}

void StaffGraphicsItemTest::testStandardStaffBoundingRect()
{
    qreal testLineHeight = 26;
    qreal testLineWidth = 4;
    int testItemWidth = 50;
    m_graphicsItem->setLineHeight(testLineHeight);
    m_graphicsItem->setLineWidth(testLineWidth);
    m_graphicsItem->setStaffType(StaffType::Standard);
    m_graphicsItem->setGeometry(0, 0, testItemWidth, m_graphicsItem->maximumHeight());
    qreal testItemHeight = m_graphicsItem->maximumHeight();

    QRectF boundingRect = m_graphicsItem->boundingRect();
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

QTEST_MAIN(StaffGraphicsItemTest)

#include "tst_staffgraphicsitemtest.moc"
