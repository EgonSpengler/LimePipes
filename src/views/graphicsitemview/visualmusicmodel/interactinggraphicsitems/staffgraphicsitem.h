/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef STAFFGRAPHICSITEM_H
#define STAFFGRAPHICSITEM_H

#include <QPen>
#include <common/defines.h>
#include "interactinggraphicsitem.h"

class QGraphicsLinearLayout;

class StaffGraphicsItem : public InteractingGraphicsItem
{
    friend class StaffGraphicsItemTest;

public:
    explicit StaffGraphicsItem(QGraphicsItem *parent = 0);

    enum { Type = StaffGraphicItem };
    int type() const { return Type; }

    StaffType staffType() const;
    void setStaffType(StaffType type);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // InteractingGraphicsItem interface
    void insertChildItem(int index, InteractingGraphicsItem *childItem);
    int measureCount() const;

private:
    int staffLineHeight() const;
    void setStaffLineHeight(qreal staffLineHeight);
    qreal penWidth() const;
    void setPenWidth(qreal width);
    void setSizeHintsForStaffType(StaffType type);
    void setWindowFrameRectForLineWidth(qreal width);
    StaffType m_staffType;
    qreal m_staffLineHeight;
    QPen m_pen;
    QGraphicsLinearLayout *m_measureLayout;
};

#endif // STAFFGRAPHICSITEM_H
