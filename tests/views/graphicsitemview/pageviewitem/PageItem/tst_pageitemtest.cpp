/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QList>
#include <QString>
#include <QtTest/QtTest>
#include <QtTest/QSignalSpy>
#include <QVariant>
#include <QCoreApplication>
#include "tst_pageitemtest.h"

PageItemTest::PageItemTest()
    : m_pageItem(0)
{
}

void PageItemTest::init()
{
    m_pageItem = new PageItem();
}

void PageItemTest::cleanup()
{
    delete m_pageItem;
}

void PageItemTest::testAppendRow()
{
    QGraphicsWidget *row = new QGraphicsWidget();
    m_pageItem->appendRow(row);
    QVERIFY2(m_pageItem->rowCount() == 1, "Failed append row");

    QGraphicsWidget *row2 = new QGraphicsWidget();
    m_pageItem->appendRow(row2);
    QVERIFY2(m_pageItem->rowAt(1) == row2, "Failed append second row");
}

void PageItemTest::testPrependRow()
{
    QGraphicsWidget *row = new QGraphicsWidget();
    m_pageItem->prependRow(row);
    QVERIFY2(m_pageItem->rowCount() == 1, "Failed prepend row");

    QGraphicsWidget *row2 = new QGraphicsWidget();
    m_pageItem->prependRow(row2);
    QVERIFY2(m_pageItem->rowAt(0) == row2, "Failed prepend second row");
}

void PageItemTest::testInsertRow()
{
    QGraphicsWidget *row1 = new QGraphicsWidget();
    QGraphicsWidget *row2 = new QGraphicsWidget();
    QGraphicsWidget *row12 = new QGraphicsWidget();

    m_pageItem->appendRow(row1);
    m_pageItem->appendRow(row2);
    m_pageItem->insertRow(1, row12);

    QVERIFY2(m_pageItem->rowCount() == 3, "Failed adding row");
    QVERIFY2(m_pageItem->rowAt(1) == row12, "Failed inserting row at right place");
    QVERIFY2(m_pageItem->rowCount() == 3, "Failed adding row");  // Just in case. rowAt should not remove item.
}

void PageItemTest::testRemoveRowIndex()
{
    QGraphicsWidget *row1 = new QGraphicsWidget();
    QGraphicsWidget *row2 = new QGraphicsWidget();
    QGraphicsWidget *row3 = new QGraphicsWidget();

    m_pageItem->appendRow(row1);
    m_pageItem->appendRow(row2);
    m_pageItem->appendRow(row3);
    QVERIFY2(m_pageItem->rowCount() == 3, "Failed inserting rows");

    m_pageItem->removeRow(1);
    QVERIFY2(m_pageItem->rowCount() == 2, "Failed removing row");
    QVERIFY2(m_pageItem->rowAt(0) == row1, "Failed removing row, row 0 wrong");
    QVERIFY2(m_pageItem->rowAt(1) == row3, "Failed removing row, row 1 wrong");
}

void PageItemTest::testRemoveRowItem()
{
    QGraphicsWidget *row1 = new QGraphicsWidget();
    QGraphicsWidget *row2 = new QGraphicsWidget();
    QGraphicsWidget *row3 = new QGraphicsWidget();

    m_pageItem->appendRow(row1);
    m_pageItem->appendRow(row2);
    m_pageItem->appendRow(row3);
    QVERIFY2(m_pageItem->rowCount() == 3, "Failed inserting rows");

    m_pageItem->removeRow(row2);
    QVERIFY2(m_pageItem->rowCount() == 2, "Failed removing row");
    QVERIFY2(m_pageItem->rowAt(0) == row1, "Failed removing row, row 0 wrong");
    QVERIFY2(m_pageItem->rowAt(1) == row3, "Failed removing row, row 1 wrong");
}

void PageItemTest::testRemainingVerticalSpace()
{
    QVERIFY2(m_pageItem->remainingVerticalSpace() > 0, "No remaining space on blank page");

    qreal spaceBefore = m_pageItem->remainingVerticalSpace();
    QGraphicsWidget *row = new QGraphicsWidget();
    m_pageItem->appendRow(row);
    QVERIFY2(spaceBefore - row->preferredHeight() == m_pageItem->remainingVerticalSpace(), "Remaining space after appending row doesn't fit");

    spaceBefore = m_pageItem->remainingVerticalSpace();
    row = new QGraphicsWidget();
    m_pageItem->prependRow(row);
    QVERIFY2(spaceBefore - row->preferredHeight() == m_pageItem->remainingVerticalSpace(), "Remaining space after prepending row doesn't fit");

    spaceBefore = m_pageItem->remainingVerticalSpace();
    row = new QGraphicsWidget();
    m_pageItem->insertRow(1, row);
    QVERIFY2(spaceBefore - row->preferredHeight() == m_pageItem->remainingVerticalSpace(), "Remaining space after inserting row doesn't fit");

    spaceBefore = m_pageItem->remainingVerticalSpace();
    m_pageItem->removeRow(row);
    QVERIFY2(spaceBefore == m_pageItem->remainingVerticalSpace() - row->preferredHeight(), "Remaining space after removing row doesn't fit");
}

void PageItemTest::testRemainingVerticalSpaceChangedSignal()
{
    // appendRow
    QSignalSpy spy(m_pageItem, SIGNAL(remainingVerticalSpaceChanged(int,int)));
    qreal remainingSpaceBefore = m_pageItem->remainingVerticalSpace();

    m_pageItem->appendRow(new QGraphicsWidget());
    QVERIFY2(spy.count() == 1, "append: Signal wasn't emitted");

    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY2(arguments.at(0).toInt() == remainingSpaceBefore, "append: Signal returned wrong value for old value");
    QVERIFY2(arguments.at(1).toInt() == m_pageItem->remainingVerticalSpace(), "append: Signal returned wrong value for new value");

    // prependRow
    remainingSpaceBefore = m_pageItem->remainingVerticalSpace();

    m_pageItem->prependRow(new QGraphicsWidget());
    QVERIFY2(spy.count() == 1, "prepend: Signal wasn't emitted");

    arguments = spy.takeFirst();
    QVERIFY2(arguments.at(0).toInt() == remainingSpaceBefore, "prepend: Signal returned wrong value for old value");
    QVERIFY2(arguments.at(1).toInt() == m_pageItem->remainingVerticalSpace(), "prepend: Signal returned wrong value for new value");

    // insertRow
    remainingSpaceBefore = m_pageItem->remainingVerticalSpace();

    m_pageItem->insertRow(1, new QGraphicsWidget());
    QVERIFY2(spy.count() == 1, "insert: Signal wasn't emitted");

    arguments = spy.takeFirst();
    QVERIFY2(arguments.at(0).toInt() == remainingSpaceBefore, "insert: Signal returned wrong value for old value");
    QVERIFY2(arguments.at(1).toInt() == m_pageItem->remainingVerticalSpace(), "insert: Signal returned wrong value for new value");

    // remove Row with index
    remainingSpaceBefore = m_pageItem->remainingVerticalSpace();

    m_pageItem->removeRow(1);
    QVERIFY2(spy.count() == 1, "remove index: Signal wasn't emitted");

    arguments = spy.takeFirst();
    QVERIFY2(arguments.at(0).toInt() == remainingSpaceBefore, "remove index: Signal returned wrong value for old value");
    QVERIFY2(arguments.at(1).toInt() == m_pageItem->remainingVerticalSpace(), "remove index: Signal returned wrong value for new value");


    // removeRow with Item
    Q_ASSERT(m_pageItem->rowCount() >= 2);
    QGraphicsWidget *testRow = new QGraphicsWidget();
    m_pageItem->insertRow(1, testRow);
    spy.takeFirst();

    remainingSpaceBefore = m_pageItem->remainingVerticalSpace();

    m_pageItem->removeRow(testRow);
    QVERIFY2(spy.count() == 1, "remove item: Signal wasn't emitted");

    arguments = spy.takeFirst();
    QVERIFY2(arguments.at(0).toInt() == remainingSpaceBefore, "remove item: Signal returned wrong value for old value");
    QVERIFY2(arguments.at(1).toInt() == m_pageItem->remainingVerticalSpace(), "remove item: Signal returned wrong value for new value");
}

void PageItemTest::testRowExceedsContentBoundsSignal()
{
     // appendRow
    QSignalSpy spy(m_pageItem, SIGNAL(lastRowExceedsContentBounds()));
    QGraphicsWidget *row = new QGraphicsWidget();
    m_pageItem->appendRow(row);
    qreal defaultRowHeight = row->preferredHeight();

    while (m_pageItem->remainingVerticalSpace() > defaultRowHeight) {
        m_pageItem->appendRow(new QGraphicsWidget());
    }
    m_pageItem->appendRow(new QGraphicsWidget());

    QVERIFY2( m_pageItem->remainingVerticalSpace() < 0, "Vertical space should be less than 0");
    QVERIFY2(spy.count() == 1, "Signal wasn't emitted by append row");

    m_pageItem->removeRow(m_pageItem->rowCount() - 1);
    Q_ASSERT(m_pageItem->remainingVerticalSpace() > 0 && m_pageItem->remainingVerticalSpace() < defaultRowHeight);
    m_pageItem->insertRow(3, new QGraphicsWidget());
    Q_ASSERT(m_pageItem->remainingVerticalSpace() < 0);

    QVERIFY2(spy.count() == 2, "Signal wasn't emitted by insert row");

    m_pageItem->removeRow(m_pageItem->rowCount() - 1);
    Q_ASSERT(m_pageItem->remainingVerticalSpace() > 0 && m_pageItem->remainingVerticalSpace() < defaultRowHeight);
    m_pageItem->prependRow(new QGraphicsWidget());
    Q_ASSERT(m_pageItem->remainingVerticalSpace() < 0);

    QVERIFY2(spy.count() == 3, "Signal wasn't emitted by prepend row");
}

QTEST_MAIN(PageItemTest)
