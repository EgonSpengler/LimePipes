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

QTEST_MAIN(StaffGraphicsItemTest)

#include "tst_staffgraphicsitemtest.moc"
