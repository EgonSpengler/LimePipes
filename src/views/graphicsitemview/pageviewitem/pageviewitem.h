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
#include "pagecontentrowitem.h"
#include "../pageviewinterface.h"
#include "../itemtypes.h"

class PageItem;
class QGraphicsLinearLayout;

class PageViewItem : public QGraphicsWidget,
                     public PageViewInterface
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

    void appendRow(QGraphicsWidget *row);
    void prependRow(QGraphicsWidget *row);
    void insertRow(int index, QGraphicsWidget *row);
    void removeRow(int rowIndex);

    QGraphicsWidget *rowAt(int index) const;

private slots:
    void rowExceedsBoundsOfPage();
    void remainingVerticalSpaceHasChanged(int oldValue, int newValue);

private:
    void prepareWidgetForRow(QGraphicsWidget *rowWidget);
    void addPage();
    void removePage(PageItem *page);
    bool isPageItemLastPage(PageItem *page) const;
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
