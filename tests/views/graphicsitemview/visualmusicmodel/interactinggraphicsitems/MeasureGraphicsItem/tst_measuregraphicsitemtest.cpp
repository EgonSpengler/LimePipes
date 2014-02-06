/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QRectF>
#include <QCoreApplication>
#include <QGraphicsLinearLayout>
#include <src/views/graphicsitemview/visualmusicmodel/interactinggraphicsitems/measuregraphicsitem.h>

class MeasureGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    MeasureGraphicsItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSymbolLayout();
    void testInsertChildItemImplementation();
    void testSetGetLineWidth();
//    void testSetLineSide();
    void testBoundingRect();
//    void testBoundingRectLineSide();

private:
    MeasureGraphicsItem *m_measureGraphicsItem;
};

MeasureGraphicsItemTest::MeasureGraphicsItemTest()
    : m_measureGraphicsItem(0)
{
}

void MeasureGraphicsItemTest::init()
{
    m_measureGraphicsItem = new MeasureGraphicsItem();
}

void MeasureGraphicsItemTest::cleanup()
{
    delete m_measureGraphicsItem;
}

void MeasureGraphicsItemTest::testSymbolLayout()
{
    QVERIFY2(m_measureGraphicsItem->layout() != 0, "No layout set");
    QVERIFY2(m_measureGraphicsItem->m_symbolLayout != 0, "Measure layout wasn't initialized");
    QVERIFY2(m_measureGraphicsItem->m_symbolLayout->spacing() == 0,
             "Spacing is not 0");

    qreal top, right, bottom, left;
    m_measureGraphicsItem->m_symbolLayout->getContentsMargins(&left, &top, &right, &bottom);
    QVERIFY2(top == 0, "Contents margin is wrong");
    QVERIFY2(right == 0, "Contents margin is wrong");
    QVERIFY2(bottom == 0, "Contents margin is wrong");
    QVERIFY2(left == 0, "Contents margin is wrong");
}

void MeasureGraphicsItemTest::testInsertChildItemImplementation()
{
    InteractingGraphicsItem *testInteractingItem1 = new InteractingGraphicsItem;
    InteractingGraphicsItem *testInteractingItem2 = new InteractingGraphicsItem;
    InteractingGraphicsItem *testInteractingItem3 = new InteractingGraphicsItem;

    m_measureGraphicsItem->insertChildItem(0, testInteractingItem1);
    QVERIFY2(m_measureGraphicsItem->m_symbolLayout->count(),
             "No child item was inserted");

    m_measureGraphicsItem->insertChildItem(1, testInteractingItem3);
    m_measureGraphicsItem->insertChildItem(1, testInteractingItem2);

    QVERIFY2(m_measureGraphicsItem->m_symbolLayout->count() == 3,
             "Not all items were inserted");
    QVERIFY2(m_measureGraphicsItem->m_symbolLayout->itemAt(1) == testInteractingItem2,
             "Item was inserted in wrong position");

    delete testInteractingItem1;
    delete testInteractingItem2;
    delete testInteractingItem3;
}

void MeasureGraphicsItemTest::testSetGetLineWidth()
{
    QVERIFY2(m_measureGraphicsItem->lineWidth() == 1,
             "Wrong default line width");

    m_measureGraphicsItem->setLineWidth(0);
    QVERIFY2(m_measureGraphicsItem->lineWidth() == 1,
             "Line width can be set to 0");

    m_measureGraphicsItem->setLineWidth(12);
    QVERIFY2(m_measureGraphicsItem->lineWidth() == 12,
             "Can't set line width");
}

void MeasureGraphicsItemTest::testBoundingRect()
{
    int testItemWidth = 200;
    int testItemHeight = 50;
    qreal testLineWidth = 2;

    m_measureGraphicsItem->setLineWidth(testLineWidth);
    m_measureGraphicsItem->setGeometry(0, 0, testItemWidth, testItemHeight);

    QRectF boundingRect(m_measureGraphicsItem->boundingRect());

    QVERIFY2(boundingRect.top() == 0, "Wrong bounding rect top");
    QVERIFY2(boundingRect.bottom() == testItemHeight, "Wrong bounding rect bottom");
    QVERIFY2(boundingRect.left() == 0, "Wrong left side of bounding rect");
    QVERIFY2(boundingRect.right() == testItemWidth, "Wrong right side of bounding rect");
}

QTEST_MAIN(MeasureGraphicsItemTest)

#include "tst_measuregraphicsitemtest.moc"
