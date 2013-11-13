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
#include "tst_pageviewitemtest.h"
#include <graphicsitemview/pageviewitem/pageviewitem.h>
#include <graphicsitemview/pageviewitem/pageitem.h>

PageViewItemTest::PageViewItemTest(QObject *parent)
    : QObject(parent),
      m_pageViewItem(0),
      m_defaultVerticalSpacePerPage(0),
      m_defaultRowItemHeight(0)
{
}

void PageViewItemTest::initTestCase()
{
    PageItem *pageItem = new PageItem();
    QGraphicsWidget *rowItem = new QGraphicsWidget();

    m_defaultVerticalSpacePerPage = pageItem->remainingVerticalSpace();
    m_defaultRowItemHeight = rowItem->preferredHeight();

    delete pageItem;
    delete rowItem;
}

void PageViewItemTest::init()
{
    m_pageViewItem = new PageViewItem();
}

void PageViewItemTest::cleanup()
{
    delete m_pageViewItem;
}

void PageViewItemTest::testInitialPageCount()
{
    QVERIFY2(m_pageViewItem->pageCount() == 1, "Failed, wrong initial pagecount");
}

void PageViewItemTest::testRowCount()
{
    m_pageViewItem->appendRow(new QGraphicsWidget());
    QVERIFY2(m_pageViewItem->rowCount() == 1, "Failed appending and counting row");
}

void PageViewItemTest::testPageCount()
{
    fillFirstPage();
    QVERIFY2(m_pageViewItem->pageCount() == 1, "Filled more than one page");

    m_pageViewItem->appendRow(new QGraphicsWidget());

    QVERIFY2(m_pageViewItem->pageCount() == 2, "No pagebreak occured");
}

void PageViewItemTest::testRowCountMultipage()
{
    fillFirstPage();
    int rowCountBefore = m_pageViewItem->rowCount();
    m_pageViewItem->appendRow(new QGraphicsWidget());

    QVERIFY2(m_pageViewItem->rowCount() == rowCountBefore + 1, "Failed row count with multipage");
}

void PageViewItemTest::testRowAt()
{
    QGraphicsWidget *row1 = new QGraphicsWidget();
    QGraphicsWidget *row2 = new QGraphicsWidget();
    QGraphicsWidget *row3 = new QGraphicsWidget();

    m_pageViewItem->appendRow(row1);
    m_pageViewItem->appendRow(row2);
    m_pageViewItem->appendRow(row3);

    QVERIFY2(m_pageViewItem->rowAt(1) == row2, "Failed getting row at index");
    QVERIFY(m_pageViewItem->rowAt(456) == 0);
    QVERIFY(m_pageViewItem->rowAt(-123) == 0);
}

void PageViewItemTest::testRowCountOfPage()
{
    fillFirstPage();
    int defaultRowCountPerPage =
            m_defaultVerticalSpacePerPage /
            m_defaultRowItemHeight;
    QVERIFY2(m_pageViewItem->rowCountOfPage(0) == defaultRowCountPerPage, "Wrong row count for page returned");

    QVERIFY2(m_pageViewItem->rowCountOfPage(123) == 0, "Too high page index doesn't return 0");
    QVERIFY2(m_pageViewItem->rowCountOfPage(-123) == 0, "Page index below 0 doesn't return 0");
}

void PageViewItemTest::testRowAtMultipage()
{
    fillFirstPage();
    int rowCountFirstPage = m_pageViewItem->rowCountOfPage(0);
    Q_ASSERT(rowCountFirstPage);

    QGraphicsWidget *row1 = new QGraphicsWidget();
    QGraphicsWidget *row2 = new QGraphicsWidget();
    QGraphicsWidget *row3 = new QGraphicsWidget();

    m_pageViewItem->appendRow(row1);
    m_pageViewItem->appendRow(row2);
    m_pageViewItem->appendRow(row3);

    QGraphicsWidget *firstRowSecondPage = m_pageViewItem->rowAt(rowCountFirstPage);
    QVERIFY2(firstRowSecondPage != 0, "Failed getting first row of second page. It's 0");
    QVERIFY2(firstRowSecondPage == row1, "First row of second page is not expected row");

    QGraphicsWidget *secondRowSecondPage = m_pageViewItem->rowAt(rowCountFirstPage + 1);
    QVERIFY2(secondRowSecondPage != 0, "Failed getting second row of second page. It's 0");
    QVERIFY2(secondRowSecondPage == row2, "Second row of second page is not expected row");
}

void PageViewItemTest::testInsertRow()
{
    fillFirstPage();
    int rowCountBeforeInsert = m_pageViewItem->rowCount();
    Q_ASSERT(rowCountBeforeInsert > 5);

    QGraphicsWidget *insertRow = new QGraphicsWidget();

    m_pageViewItem->insertRow(5, insertRow);

    QVERIFY2(m_pageViewItem->rowCount() == rowCountBeforeInsert + 1, "Failed inserting row");
    QVERIFY2(m_pageViewItem->rowAt(5) == insertRow, "Row was inserted in wrong place");
}

void PageViewItemTest::testInsertRowMultipage()
{
    fillFirstPage();
    int rowCountOfFirstPage = m_pageViewItem->rowCountOfPage(0);
    Q_ASSERT(rowCountOfFirstPage > 5);

    QGraphicsWidget *insertRow = new QGraphicsWidget();
    QGraphicsWidget *lastRow = m_pageViewItem->rowAt(m_pageViewItem->rowCount() - 1);
    m_pageViewItem->insertRow(5, insertRow);

    QVERIFY2(m_pageViewItem->rowAt(5) == insertRow, "Failed inserting row");
    QVERIFY2(m_pageViewItem->pageCount() == 2, "Pagebreak failed while inserting row");
    QVERIFY2(m_pageViewItem->rowAt(m_pageViewItem->rowCount() - 1) == lastRow, "Wrong row on second page");
}

void PageViewItemTest::testInsertRowMultipageHighRow()
{
    fillFirstPage();

    QGraphicsWidget *highRow = new QGraphicsWidget();
    highRow->setPreferredHeight(3 * m_defaultRowItemHeight);
    Q_ASSERT(m_pageViewItem->rowCountOfPage(0) > 5);

    m_pageViewItem->insertRow(5, highRow);

    QVERIFY2(m_pageViewItem->rowCountOfPage(1) == 3, "Not all rows where moved to next page");
}

void PageViewItemTest::testPrependRow()
{
    fillFirstPage();
    QGraphicsWidget *prependRow = new QGraphicsWidget();

    m_pageViewItem->prependRow(prependRow);

    QVERIFY2(m_pageViewItem->rowAt(0) == prependRow, "Failed prepending row");
}

void PageViewItemTest::testRemoveRow()
{
    int removeRowIndex = 4;
    fillFirstPage();
    Q_ASSERT(m_pageViewItem->rowCount() > removeRowIndex + 1);

    QGraphicsWidget *rowAfterDeleteRow = m_pageViewItem->rowAt(removeRowIndex + 1);

    m_pageViewItem->removeRow(removeRowIndex);

    QVERIFY2(m_pageViewItem->rowAt(removeRowIndex) == rowAfterDeleteRow, "Failed removing row");
}

void PageViewItemTest::testRemoveRowMultipage()
{
    int removeRowIndex = 4;
    fillFirstPage();
    Q_ASSERT(m_pageViewItem->rowCount() > removeRowIndex + 1);

    m_pageViewItem->appendRow(new QGraphicsWidget());
    Q_ASSERT(m_pageViewItem->pageCount() == 2);

    int rowCountOfFirstPageBefore = m_pageViewItem->rowCountOfPage(0);
    m_pageViewItem->removeRow(removeRowIndex);

    QVERIFY2(rowCountOfFirstPageBefore == m_pageViewItem->rowCountOfPage(0), "Row wasn't moved from second to first page");
}

void PageViewItemTest::testRemoveRowMultipageHighRow()
{
    int removeRowIndex = 4;
    qreal highRowHeight = 3 * m_defaultRowItemHeight;
    fillFirstPage();

    // High row
    for (int i=0; i<3; i++) {
        m_pageViewItem->removeRow(removeRowIndex);
    }

    // Filled first page with one high row
    QGraphicsWidget *highRow = new QGraphicsWidget();
    highRow->setPreferredHeight(highRowHeight);
    m_pageViewItem->insertRow(removeRowIndex, highRow);
    Q_ASSERT(m_pageViewItem->pageCount() == 1);

    // Page 2 with three normal high rows
    for (int i=0; i<3; i++) {
        m_pageViewItem->appendRow(new QGraphicsWidget());
    }
    Q_ASSERT(m_pageViewItem->pageCount() == 2);
    Q_ASSERT(m_pageViewItem->rowCountOfPage(1) == 3);

    int rowCountOfFirstPageBefore = m_pageViewItem->rowCountOfPage(0);

    m_pageViewItem->removeRow(removeRowIndex);

    QVERIFY2(rowCountOfFirstPageBefore + 2 == m_pageViewItem->rowCountOfPage(0),
             "Not enough rows where moved from second page to first page after removing high row");
}

void PageViewItemTest::testRemoveLastEmptyPage()
{
    fillFirstPage();
    m_pageViewItem->appendRow(new QGraphicsWidget());
    Q_ASSERT(m_pageViewItem->pageCount() == 2);

    m_pageViewItem->removeRow(4);
    Q_ASSERT(m_pageViewItem->rowCountOfPage(1) == 0);

    QVERIFY2(m_pageViewItem->pageCount() == 1, "Last empty page wasn't removed after removing row");
}

void PageViewItemTest::fillFirstPage()
{
    int verticalSpaceOfFirstPage = m_defaultVerticalSpacePerPage;
    QGraphicsWidget *row = 0;

    do {
        row = new QGraphicsWidget();
        verticalSpaceOfFirstPage -= row->preferredHeight();
        m_pageViewItem->appendRow(row);
    } while (verticalSpaceOfFirstPage > row->preferredHeight());
}

QTEST_MAIN(PageViewItemTest)
