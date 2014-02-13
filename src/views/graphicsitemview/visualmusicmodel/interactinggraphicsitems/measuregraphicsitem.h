/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MEASUREGRAPHICSITEM_H
#define MEASUREGRAPHICSITEM_H

#include <QPen>
#include <common/defines.h>
#include "interactinggraphicsitem.h"

class QGraphicsLinearLayout;

class MeasureGraphicsItem : public InteractingGraphicsItem
{
    friend class MeasureGraphicsItemTest;

public:
    explicit MeasureGraphicsItem(QGraphicsItem *parent = 0);

    enum Type { Type = MeasureGraphic };
    int type() const { return Type; }

    void setLineWidth(qreal width);
    qreal lineWidth() const;

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // InteractingGraphicsItem interface
public:
    void insertChildItem(int index, InteractingGraphicsItem *childItem);
    void setData(const QVariant &value, int key);

private:
    QGraphicsLinearLayout *m_symbolLayout;
    QPen m_linePen;
};

#endif // MEASUREGRAPHICSITEM_H
