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

class PageContentRowItem;
class QGraphicsLinearLayout;

class PageItem : public QGraphicsWidget
{
    Q_OBJECT

public:
    explicit PageItem(QGraphicsItem *parent = 0);

    enum { Type = PageItemType };
    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPageAndContentRectFromPrinter(const QPrinter &printer);

    int remainingVerticalSpace() const;
    int rowCount() const;

    PageContentRowItem *rowAt(int index);

    void appendRow(PageContentRowItem *row);
    void insertRow(int index, PageContentRowItem *row);
    void prependRow(PageContentRowItem *row);
    void removeRow(int index);
    void removeRow(PageContentRowItem *row);

signals:
    void remainingVerticalSpaceChanged(int oldValue, int newValue);

private:
    int m_shortEdgeWidth;
    QRectF m_pageRect;
    QRectF m_pageContentRect;
    QGraphicsLinearLayout *m_layout;
};

#endif // PAGEITEM_H
