/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef INTERACTINGGRAPHICSITEM_H
#define INTERACTINGGRAPHICSITEM_H

#include <QGraphicsWidget>
#include "../visualiteminterface.h"

class InteractingGraphicsItem : public QGraphicsWidget
{
    friend class InteractingGraphicsItemTest;

public:
    explicit InteractingGraphicsItem(QGraphicsItem *parent = 0);

    VisualItemInterface *visualItem() const;
    void setVisualItem(VisualItemInterface *visualItem);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    VisualItemInterface *m_visualItem;
};

#endif // INTERACTINGGRAPHICSITEM_H
