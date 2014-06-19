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

#include <common/defines.h>
#include <common/settingsobserver.h>

class QPrinter;
class QPageLayout;
class QGraphicsLinearLayout;

class PageItem : public QGraphicsWidget,
                 public SettingsObserver
{
    Q_OBJECT

public:
    explicit PageItem(QGraphicsItem *parent = 0);

    enum { Type = PageItemType };
    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int remainingVerticalSpace() const;
    int rowCount() const;
    int indexOfRow(QGraphicsWidget *row);

    QGraphicsWidget *rowAt(int index);

    void appendRow(QGraphicsWidget *row);
    void prependRow(QGraphicsWidget *row);
    void insertRow(int index, QGraphicsWidget *row);

    void removeRow(int index);
    void removeRow(QGraphicsWidget *row);

    // SettingsObserver interface
    void notify();

signals:
    void remainingVerticalSpaceChanged(int oldValue, int newValue);
    void lastRowExceedsContentBounds();

private:
    void setPageLayout(const QPageLayout &layout);
    void prepareWidgetForRow(QGraphicsWidget *rowWidget);
    bool isValidRowIndex(int rowIndex);
    QRectF m_pageRect;
    QRectF m_pageContentRect;
    QGraphicsLinearLayout *m_layout;
};

#endif // PAGEITEM_H
