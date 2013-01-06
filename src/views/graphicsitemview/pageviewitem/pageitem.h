/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PAGEITEM_H
#define PAGEITEM_H

#include <QGraphicsWidget>
#include "../itemtypes.h"
#include "pagecontentitem.h"

class PageContentRowItem;

class PageItem : public QGraphicsWidget
{
public:
    explicit PageItem(QGraphicsItem *parent = 0);

    enum { Type = PageItemType };
    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPageAndPaperRectFromPrinter(const QPrinter &printer);

    int remainingVerticalSpace() const;
    void appendRow(PageContentRowItem *row);
    void prependRow(PageContentRowItem *row);
    void insertRow(int index, PageContentRowItem *row);
    int rowCount() const;
    PageContentRowItem *rowAt(int index);
    void removeRow(int index);
    void removeRow(PageContentRowItem *row);

private:
    int m_shortEdgeWidth;
    QRectF m_pageRect;
    QRectF m_pageContentRect;
    PageContentItem *m_pageContentItem;
};

#endif // PAGEITEM_H
