/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <QFocusEvent>
#include <graphicsitemview/visualmusicmodel/interactinggraphicsitems/graphicitems/graphicstextitem.h>

class GraphicsTextItemTest : public QObject
{
    Q_OBJECT

public:
    GraphicsTextItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testFocusIn();
    void testFocusOut();
    void testSetGetAlignment();

private:
    GraphicsTextItem *m_textItem;
};

GraphicsTextItemTest::GraphicsTextItemTest()
{
}

void GraphicsTextItemTest::init()
{
    m_textItem = new GraphicsTextItem();
}

void GraphicsTextItemTest::cleanup()
{
    delete m_textItem;
}

void GraphicsTextItemTest::testFocusIn()
{
    QSignalSpy spy(m_textItem, SIGNAL(focusIn()));

    QFocusEvent focusEvent(QEvent::FocusIn);
    m_textItem->focusInEvent(&focusEvent);

    QVERIFY2(spy.count() == 1, "No signal on focus in emitted");
}

void GraphicsTextItemTest::testFocusOut()
{
    QSignalSpy spy(m_textItem, SIGNAL(focusOut()));

    QFocusEvent focusEvent(QEvent::FocusOut);
    m_textItem->focusOutEvent(&focusEvent);

    QVERIFY2(spy.count() == 1, "No signal on focus out emitted");
}

void GraphicsTextItemTest::testSetGetAlignment()
{
    Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignTop;
    Q_ASSERT(m_textItem->alignment() != alignment);

    m_textItem->setAlignment(alignment);
    QVERIFY2(m_textItem->alignment() == alignment, "Alignment wasn't set or can't get back");
}

QTEST_MAIN(GraphicsTextItemTest)

#include "tst_graphicstextitemtest.moc"
