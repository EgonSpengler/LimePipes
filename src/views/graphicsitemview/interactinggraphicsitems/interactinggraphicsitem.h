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
#include "../interactingiteminterface.h"

class InteractingGraphicsItem : public QGraphicsWidget
{
    friend class InteractingGraphicsItemTest;

public:
    explicit InteractingGraphicsItem(QGraphicsItem *parent = 0);
    virtual ~InteractingGraphicsItem() {}

    InteractingItemInterface *interactingItem() const;
    void setInteractingItem(InteractingItemInterface *interactingItem);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    InteractingItemInterface *m_visualItem;
};

#endif // INTERACTINGGRAPHICSITEM_H
