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

class SymbolGraphicsItem;
class QGraphicsLinearLayout;

class MeasureGraphicsItem : public InteractingGraphicsItem
{
    friend class MeasureGraphicsItemTest;

public:
    explicit MeasureGraphicsItem(QGraphicsItem *parent = 0);

    enum { Type = MeasureGraphicsItemType };
    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QGraphicsItem *dropItemAt(const QPointF &point);

    // InteractingGraphicsItem interface
public:
    void insertChildItem(int index, InteractingGraphicsItem *childItem);
    void setData(const QVariant &value, int key);
    void setGeometry(const QRectF& rect);

protected:
    void musicFontHasChanged(const MusicFontPtr &musicFont);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    void layoutSymbolItems();
    void clearEndOfDrag();
    QList<QRectF> symbolGeometries() const;
    void setPenWidth(qreal width);
    qreal penWidth() const;
    void setSymbolGeometry(SymbolGraphicsItem *symbolItem, const QRectF& rect);
    void setSymbolGeometry(SymbolGraphicsItem *item, int i);
    QList<SymbolGraphicsItem*> m_symbolItems;
    QPen m_linePen;
    QList<QRectF> m_dragMoveRects;
    QGraphicsLinearLayout *m_layout;
};

#endif // MEASUREGRAPHICSITEM_H
