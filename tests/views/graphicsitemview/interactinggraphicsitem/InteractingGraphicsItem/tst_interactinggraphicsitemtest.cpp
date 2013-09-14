/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <views/graphicsitemview/interactinggraphicsitems/interactinggraphicsitem.h>
#include "visualitemdummy.h"

class InteractingGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    InteractingGraphicsItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetVisualItemInterface();
    void testMousePressEvent();
    void testMouseMoveEvent();
    void testMouseReleseEvent();
    void testMouseDoubleClickEvent();

private:
    InteractingGraphicsItem *m_interactingGraphicsItem;
    VisualItemDummy *m_visualItemDummy;
};

InteractingGraphicsItemTest::InteractingGraphicsItemTest()
    : m_interactingGraphicsItem(0),
      m_visualItemDummy(0)
{
}

void InteractingGraphicsItemTest::init()
{
    m_visualItemDummy = new VisualItemDummy();
    m_interactingGraphicsItem = new InteractingGraphicsItem();
    m_interactingGraphicsItem->setVisualItem(m_visualItemDummy);
}

void InteractingGraphicsItemTest::cleanup()
{
    delete m_interactingGraphicsItem;
    delete m_visualItemDummy;
}

void InteractingGraphicsItemTest::testSetGetVisualItemInterface()
{
    VisualItemInterface *visualItem = new VisualItemDummy();
    m_interactingGraphicsItem->setVisualItem(visualItem);

    QVERIFY2(m_interactingGraphicsItem->visualItem() == visualItem,
             "Can't get visual item back from interacting item");
}

void InteractingGraphicsItemTest::testMousePressEvent()
{
    QSignalSpy spy(m_visualItemDummy, SIGNAL(mousePressEventTriggered()));

    QGraphicsSceneMouseEvent *mouseEvent = new QGraphicsSceneMouseEvent();
    m_interactingGraphicsItem->mousePressEvent(mouseEvent);

    QVERIFY2(spy.count() == 1, "Mouse press event wasn't called on VisualItemInterface");

    delete mouseEvent;
}

void InteractingGraphicsItemTest::testMouseMoveEvent()
{
    QSignalSpy spy(m_visualItemDummy, SIGNAL(mouseMoveEventTriggered()));

    QGraphicsSceneMouseEvent *mouseEvent = new QGraphicsSceneMouseEvent();
    m_interactingGraphicsItem->mouseMoveEvent(mouseEvent);

    QVERIFY2(spy.count() == 1, "Mouse move event wasn't called on VisualItemInterface");

    delete mouseEvent;
}

void InteractingGraphicsItemTest::testMouseReleseEvent()
{
    QSignalSpy spy(m_visualItemDummy, SIGNAL(mouseReleaseEventTriggered()));

    QGraphicsSceneMouseEvent *mouseEvent = new QGraphicsSceneMouseEvent();
    m_interactingGraphicsItem->mouseReleaseEvent(mouseEvent);

    QVERIFY2(spy.count() == 1, "Mouse release event wasn't called on VisualItemInterface");

    delete mouseEvent;
}

void InteractingGraphicsItemTest::testMouseDoubleClickEvent()
{
    QSignalSpy spy(m_visualItemDummy, SIGNAL(mouseDoubleClickEventTriggered()));

    QGraphicsSceneMouseEvent *mouseEvent = new QGraphicsSceneMouseEvent();
    m_interactingGraphicsItem->mouseDoubleClickEvent(mouseEvent);

    QVERIFY2(spy.count() == 1, "Mouse double click event wasn't called on VisualItemInterface");

    delete mouseEvent;
}

QTEST_MAIN(InteractingGraphicsItemTest)

#include "tst_interactinggraphicsitemtest.moc"
