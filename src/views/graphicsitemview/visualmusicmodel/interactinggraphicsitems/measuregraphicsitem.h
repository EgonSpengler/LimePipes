/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MEASUREGRAPHICSITEM_H
#define MEASUREGRAPHICSITEM_H

#include <QList>
#include <QPen>
#include <common/defines.h>
#include "interactinggraphicsitem.h"

class QGraphicsLinearLayout;

class MeasureGraphicsItem : public InteractingGraphicsItem
{
    friend class MeasureGraphicsItemTest;

public:
    explicit MeasureGraphicsItem(QGraphicsItem *parent = 0);

    enum { Type = MeasureGraphicsItemType };
    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // InteractingGraphicsItem interface
public:
    void insertChildItem(int index, InteractingGraphicsItem *childItem);
    void setData(const QVariant &value, int key);

    // InteractingGraphicsItem interface
    void clearEndOfDrag();
protected:
    void musicFontHasChanged(const MusicFontPtr &musicFont);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    void setPenWidth(qreal width);
    qreal penWidth() const;
    QList<InteractingGraphicsItem*> m_symbolItems;
//    QGraphicsLinearLayout *m_symbolLayout;
    QPen m_linePen;
    QList<QRectF> m_dragMoveRects;
    QGraphicsWidget *m_dragGapItem;
};

#endif // MEASUREGRAPHICSITEM_H
