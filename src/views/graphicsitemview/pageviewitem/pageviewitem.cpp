/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pageviewitem.h"
#include "pagecontentrowitem.h"
#include "pageitem.h"
#include <QGraphicsLinearLayout>

#include <QDebug>

PageViewItem::PageViewItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
    m_pageLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    m_pageLayout->setSpacing(30.0);

    addPage();
}

QRectF PageViewItem::boundingRect() const
{
    return m_pageLayout->geometry();
}

int PageViewItem::pageCount() const
{
    return m_pageLayout->count();
}

int PageViewItem::rowCount() const
{
    int rowCount = 0;
    PageItem *page = 0;

    for (int i = 0; i < m_pageLayout->count(); i++) {
        page = pageAt(i);
        if (page != 0) {
            rowCount += page->rowCount();
        }
    }

    return rowCount;
}

int PageViewItem::rowCountOfPage(int index) const
{
    PageItem *page= pageAt(index);

    if (!page) return 0;

    return page->rowCount();
}

void PageViewItem::appendRow(PageContentRowItem *row)
{
    PageItem *lastPage = getLastPage();

    if (lastPage->remainingVerticalSpace() < row->preferredHeight()) {
        addPage();
        lastPage = getLastPage();
    }
    lastPage->appendRow(row);
}

void PageViewItem::prependRow(PageContentRowItem *row)
{
    insertRow(0, row);
}

PageContentRowItem *PageViewItem::rowAt(int index)
{
    int row_count = rowCount();
    if (index < 0 || index > row_count)
        return 0;

    PageItem *pageContainingIndex = pageWithRowIndex(index);
    Q_ASSERT(pageContainingIndex);

    return pageContainingIndex->rowAt(index - firstIndexOfPage(pageContainingIndex));
}

void PageViewItem::removeRow(int rowIndex)
{
    PageItem *page = pageWithRowIndex(rowIndex);
    page->removeRow(rowIndex - firstIndexOfPage(page));
}

void PageViewItem::insertRow(int index, PageContentRowItem *row)
{
    PageItem *insertPage = pageWithRowIndex(index);
    int firstIndexOfInsertPage = firstIndexOfPage(insertPage);

    insertPage->insertRow(index - firstIndexOfInsertPage, row);
}

void PageViewItem::rowExceedsBoundsOfPage()
{
    PageItem *page = qobject_cast<PageItem*>(QObject::sender());
    Q_ASSERT(page);
    Q_ASSERT(page->remainingVerticalSpace() < 0);

    int nextPageIndex = indexOfPage(page) + 1;

    PageItem *nextPage = pageAt(nextPageIndex);
    if (!nextPage)
        addPage();
    nextPage = pageAt(nextPageIndex);

    while (page->remainingVerticalSpace() < 0) {
        PageContentRowItem *lastRowOfPage = page->rowAt(page->rowCount() - 1);
        Q_ASSERT(lastRowOfPage);

        nextPage->prependRow(lastRowOfPage);
    }
}

void PageViewItem::remainingVerticalSpaceHasChanged(int oldValue, int newValue)
{
    PageItem *page = qobject_cast<PageItem*>(QObject::sender());
    Q_ASSERT(page);
    int pageIndex = indexOfPage(page);
    PageItem *nextPage = pageAt(pageIndex + 1);

    if (!nextPage ||
            isPageItemLastPage(page))
        return;

    PageContentRowItem *firstRowOfNextPage = nextPage->rowAt(0);

    while (firstRowOfNextPage &&
        page->remainingVerticalSpace() >= firstRowOfNextPage->preferredHeight()) {

        nextPage->removeRow(firstRowOfNextPage);
        page->appendRow(firstRowOfNextPage);
        firstRowOfNextPage = nextPage->rowAt(0);

        // Remove last page if empty
        if (isPageItemLastPage(nextPage) &&
                nextPage->rowCount() == 0) {

            removePage(nextPage);
            nextPage = 0;
            break;
        }
    }
}

int PageViewItem::indexOfPage(PageItem *page) const
{
    int i = 0;
    for (; i < m_pageLayout->count(); i++) {
        if (page == pageAt(i))
            break;
    }
    return i;
}

void PageViewItem::addPage()
{
    PageItem *page = new PageItem(this);
    m_pageLayout->addItem(page);
    m_pages.append(page);

    connect(page, SIGNAL(lastRowExceedsContentBounds()), this, SLOT(rowExceedsBoundsOfPage()));
    connect(page, SIGNAL(remainingVerticalSpaceChanged(int,int)), this, SLOT(remainingVerticalSpaceHasChanged(int,int)));
}

void PageViewItem::removePage(PageItem *page)
{
    m_pageLayout->removeItem(page);
}

bool PageViewItem::isPageItemLastPage(PageItem *page)
{
    return indexOfPage(page) == m_pageLayout->count() - 1;
}

PageItem *PageViewItem::pageAt(int pageIndex) const
{
    if (pageIndex >= m_pageLayout->count() ||
            pageIndex < 0)
        return 0;
    return pageForGraphicsItem(m_pageLayout->itemAt(pageIndex)->graphicsItem());
}

PageItem *PageViewItem::pageForGraphicsItem(QGraphicsItem *item) const
{
    return qgraphicsitem_cast<PageItem *>(item);
}

PageItem *PageViewItem::getLastPage() const
{
    Q_ASSERT(m_pageLayout->count());

    return pageAt(m_pageLayout->count() - 1);
}

PageItem *PageViewItem::pageWithRowIndex(int rowIndex) const
{
    Q_ASSERT(m_pageLayout->count());

    PageItem *currentPage = 0;
    int currentPageFirstIndex = 0;
    int currentPageLastIndex = 0;

    for (int i=0; i < m_pageLayout->count(); i++) {
        currentPage = pageAt(i);
        currentPageFirstIndex = firstIndexOfPage(currentPage);
        currentPageLastIndex = currentPageFirstIndex + currentPage->rowCount() - 1;

        if (rowIndex >= currentPageFirstIndex &&
                rowIndex <= currentPageLastIndex)
            return currentPage;
    }

    return 0;
}

int PageViewItem::firstIndexOfPage(const PageItem *page) const
{
    Q_ASSERT(m_pageLayout->count());

    int firstIndexOfCurrentPage = 0;
    PageItem *currentPage = 0;

    for (int i=0; i < m_pageLayout->count(); i++) {
        currentPage = pageAt(i);
        if (currentPage == page)
            return firstIndexOfCurrentPage;

        // Set first index of next page
        firstIndexOfCurrentPage += currentPage->rowCount();
    }

    return firstIndexOfCurrentPage;
}
