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
#include <QGraphicsSceneContextMenuEvent>
#include <views/graphicsitemview/interactinggraphicsitems/interactinggraphicsitem.h>
#include "iteminteractiondummy.h"

class InteractingGraphicsItemTest : public QObject
{
    Q_OBJECT

public:
    InteractingGraphicsItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetInteractingItemInterface();
    void testMousePressEvent();
    void testMouseMoveEvent();
    void testMouseReleseEvent();
    void testMouseDoubleClickEvent();
    void testContextMenuEvent();

private:
    InteractingGraphicsItem *m_interactingGraphicsItem;
    ItemInteractionDummy *m_interactingItemDummy;
};

InteractingGraphicsItemTest::InteractingGraphicsItemTest()
    : m_interactingGraphicsItem(0),
      m_interactingItemDummy(0)
{
}

void InteractingGraphicsItemTest::init()
{
    m_interactingItemDummy = new ItemInteractionDummy();
    m_interactingGraphicsItem = new InteractingGraphicsItem();
    m_interactingGraphicsItem->setItemInteraction(m_interactingItemDummy);
}

void InteractingGraphicsItemTest::cleanup()
{
    delete m_interactingGraphicsItem;
    delete m_interactingItemDummy;
}

void InteractingGraphicsItemTest::testSetGetInteractingItemInterface()
{
    ItemInteraction *visualItem = new ItemInteractionDummy();
    m_interactingGraphicsItem->setItemInteraction(visualItem);

    QVERIFY2(m_interactingGraphicsItem->itemInteraction() == visualItem,
             "Can't get visual item back from interacting item");
}

void InteractingGraphicsItemTest::testMousePressEvent()
{
    QSignalSpy spy(m_interactingItemDummy, SIGNAL(mousePressEventTriggered()));

    QGraphicsSceneMouseEvent *mouseEvent = new QGraphicsSceneMouseEvent();
    m_interactingGraphicsItem->mousePressEvent(mouseEvent);

    QVERIFY2(spy.count() == 1, "Mouse press event wasn't called on VisualItemInterface");

    delete mouseEvent;
}

void InteractingGraphicsItemTest::testMouseMoveEvent()
{
    QSignalSpy spy(m_interactingItemDummy, SIGNAL(mouseMoveEventTriggered()));

    QGraphicsSceneMouseEvent *mouseEvent = new QGraphicsSceneMouseEvent();
    m_interactingGraphicsItem->mouseMoveEvent(mouseEvent);

    QVERIFY2(spy.count() == 1, "Mouse move event wasn't called on VisualItemInterface");

    delete mouseEvent;
}

void InteractingGraphicsItemTest::testMouseReleseEvent()
{
    QSignalSpy spy(m_interactingItemDummy, SIGNAL(mouseReleaseEventTriggered()));

    QGraphicsSceneMouseEvent *mouseEvent = new QGraphicsSceneMouseEvent();
    m_interactingGraphicsItem->mouseReleaseEvent(mouseEvent);

    QVERIFY2(spy.count() == 1, "Mouse release event wasn't called on VisualItemInterface");

    delete mouseEvent;
}

void InteractingGraphicsItemTest::testMouseDoubleClickEvent()
{
    QSignalSpy spy(m_interactingItemDummy, SIGNAL(mouseDoubleClickEventTriggered()));

    QGraphicsSceneMouseEvent *mouseEvent = new QGraphicsSceneMouseEvent();
    m_interactingGraphicsItem->mouseDoubleClickEvent(mouseEvent);

    QVERIFY2(spy.count() == 1, "Mouse double click event wasn't called on VisualItemInterface");

    delete mouseEvent;
}

void InteractingGraphicsItemTest::testContextMenuEvent()
{
    QSignalSpy spy(m_interactingItemDummy, SIGNAL(contextMenuEventTriggered()));

    QGraphicsSceneContextMenuEvent *contextMenuEvent = new QGraphicsSceneContextMenuEvent();
    m_interactingGraphicsItem->contextMenuEvent(contextMenuEvent);

    QVERIFY2(spy.count() == 1, "context menu event wasn't called on VisualItemInterface");

    delete contextMenuEvent;
}

QTEST_MAIN(InteractingGraphicsItemTest)

#include "tst_interactinggraphicsitemtest.moc"
