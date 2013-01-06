/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest/QtTest>
#include <QCoreApplication>
#include <views/graphicsitemview/pageviewitem/pagecontentrowitem.h>
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
    PageContentRowItem *row = new PageContentRowItem();
    m_pageItem->appendRow(row);
    QVERIFY2(m_pageItem->rowCount() == 1, "Failed append row");

    PageContentRowItem *row2 = new PageContentRowItem();
    m_pageItem->appendRow(row2);
    QVERIFY2(m_pageItem->rowAt(1) == row2, "Failed append second row");
}

void PageItemTest::testPrependRow()
{
    PageContentRowItem *row = new PageContentRowItem();
    m_pageItem->prependRow(row);
    QVERIFY2(m_pageItem->rowCount() == 1, "Failed prepend row");

    PageContentRowItem *row2 = new PageContentRowItem();
    m_pageItem->prependRow(row2);
    QVERIFY2(m_pageItem->rowAt(0) == row2, "Failed prepend second row");
}

void PageItemTest::testInsertRow()
{
    PageContentRowItem *row1 = new PageContentRowItem();
    PageContentRowItem *row2 = new PageContentRowItem();
    PageContentRowItem *row12 = new PageContentRowItem();

    m_pageItem->appendRow(row1);
    m_pageItem->appendRow(row2);
    m_pageItem->insertRow(1, row12);

    QVERIFY2(m_pageItem->rowCount() == 3, "Failed adding row");
    QVERIFY2(m_pageItem->rowAt(1) == row12, "Failed inserting row at right place");
    QVERIFY2(m_pageItem->rowCount() == 3, "Failed adding row");  // Just in case. rowAt should not remove item.
}

void PageItemTest::testRemoveRowIndex()
{
    PageContentRowItem *row1 = new PageContentRowItem();
    PageContentRowItem *row2 = new PageContentRowItem();
    PageContentRowItem *row3 = new PageContentRowItem();

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
    PageContentRowItem *row1 = new PageContentRowItem();
    PageContentRowItem *row2 = new PageContentRowItem();
    PageContentRowItem *row3 = new PageContentRowItem();

    m_pageItem->appendRow(row1);
    m_pageItem->appendRow(row2);
    m_pageItem->appendRow(row3);
    QVERIFY2(m_pageItem->rowCount() == 3, "Failed inserting rows");

    m_pageItem->removeRow(row2);
    QVERIFY2(m_pageItem->rowCount() == 2, "Failed removing row");
    QVERIFY2(m_pageItem->rowAt(0) == row1, "Failed removing row, row 0 wrong");
    QVERIFY2(m_pageItem->rowAt(1) == row3, "Failed removing row, row 1 wrong");
}

QTEST_MAIN(PageItemTest)
