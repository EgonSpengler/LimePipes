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
class BaseEngraver;

class MeasureGraphicsItem : public InteractingGraphicsItem
{
    Q_OBJECT
    friend class MeasureGraphicsItemTest;

public:
    explicit MeasureGraphicsItem(QGraphicsItem *parent = 0);
    ~MeasureGraphicsItem();

    enum { Type = MeasureGraphicsItemType };
    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QGraphicsItem *dropItemAt(const QPointF &point);

    // InteractingGraphicsItem interface
    void insertChildItem(int index, InteractingGraphicsItem *childItem);
    void removeChildItem(InteractingGraphicsItem *childItem);
    void setData(const QVariant &value, int key);
    void setGeometry(const QRectF& rect);

    void appendEngraver(BaseEngraver *engraver);

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void musicFontHasChanged(const MusicFontPtr &musicFont);

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
    QList<BaseEngraver*> m_engravers;
};

#endif // MEASUREGRAPHICSITEM_H
