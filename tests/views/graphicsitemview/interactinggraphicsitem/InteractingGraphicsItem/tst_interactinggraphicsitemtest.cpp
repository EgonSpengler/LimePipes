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

private:
    InteractingGraphicsItem *m_interactingGraphicsItem;

};

InteractingGraphicsItemTest::InteractingGraphicsItemTest()
    : m_interactingGraphicsItem(0)
{
}

void InteractingGraphicsItemTest::init()
{
    m_interactingGraphicsItem = new InteractingGraphicsItem();
}

void InteractingGraphicsItemTest::cleanup()
{
    delete m_interactingGraphicsItem;
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
    VisualItemDummy *dummy = new VisualItemDummy();
    QSignalSpy spy(dummy, SIGNAL(mousePressEventTriggered()));
    m_interactingGraphicsItem->setVisualItem(dummy);
}

QTEST_MAIN(InteractingGraphicsItemTest)

#include "tst_interactinggraphicsitemtest.moc"
