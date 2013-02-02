/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PAGEVIEWITEM_H
#define PAGEVIEWITEM_H

#include <QGraphicsWidget>
#include <QList>
#include "../itemtypes.h"

class PageItem;
class PageContentRowItem;
class QGraphicsLinearLayout;

class PageViewItem : public QGraphicsWidget
{
    Q_OBJECT
public:
    PageViewItem(QGraphicsItem *parent = 0);

    enum { Type = PageViewItemType };
    int type() const { return Type; }

    QRectF boundingRect() const;

    int pageCount() const;
    int rowCount() const;
    int rowCountOfPage(int index) const;

    void appendRow(PageContentRowItem *row);
    void prependRow(PageContentRowItem *row);
    void insertRow(int index, PageContentRowItem *row);

    PageContentRowItem *rowAt(int index);

    void removeRow(int rowIndex);

private slots:
    void rowExceedsBoundsOfPage();
    void remainingVerticalSpaceHasChanged(int oldValue, int newValue);

private:
    void addPage();
    void removePage(PageItem *page);
    bool isPageItemLastPage(PageItem *page);
    PageItem *pageAt(int pageIndex) const;
    PageItem *getLastPage() const;
    PageItem *pageWithRowIndex(int rowIndex) const;
    PageItem *pageForGraphicsItem(QGraphicsItem *item) const;
    int firstIndexOfPage(const PageItem *page) const;
    int indexOfPage(PageItem *page) const;
    QGraphicsLinearLayout *m_pageLayout;
    QList<PageItem*> m_pages;
};

#endif // PAGEVIEWITEM_H
