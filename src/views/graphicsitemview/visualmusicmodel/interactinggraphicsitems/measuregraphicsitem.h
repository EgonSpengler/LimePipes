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
    void setGeometry(const QRectF& rect);

    void setSymbolGeometry(SymbolGraphicsItem *item, int i);
protected:
    void musicFontHasChanged(const MusicFontPtr &musicFont);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    void clearEndOfDrag();
    void layoutSymbolItems();
    QList<QRectF> symbolGeometries() const;
    void setPenWidth(qreal width);
    qreal penWidth() const;
    void setSymbolGeometry(SymbolGraphicsItem *symbolItem, const QRectF& rect);
    QList<SymbolGraphicsItem*> m_symbolItems;
    QPen m_linePen;
    QList<QRectF> m_dragMoveRects;
};

#endif // MEASUREGRAPHICSITEM_H
