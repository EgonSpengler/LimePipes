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

class QPrinter;
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

    QGraphicsWidget *rowAt(int index);

    void appendRow(QGraphicsWidget *row);
    void prependRow(QGraphicsWidget *row);
    void insertRow(int index, QGraphicsWidget *row);

    void removeRow(int index);
    void removeRow(QGraphicsWidget *row);

signals:
    void remainingVerticalSpaceChanged(int oldValue, int newValue);
    void lastRowExceedsContentBounds();

private:
    void prepareWidgetForRow(QGraphicsWidget *rowWidget);
    bool isValidRowIndex(int rowIndex);
    int m_shortEdgeWidth;
    QRectF m_pageRect;
    QRectF m_pageContentRect;
    QGraphicsLinearLayout *m_layout;
};

#endif // PAGEITEM_H
