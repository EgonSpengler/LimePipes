/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INTERACTINGITEMINTERFACE_H
#define INTERACTINGITEMINTERFACE_H

class QGraphicsSceneMouseEvent;
class QGraphicsSceneContextMenuEvent;

class InteractingItemInterface
{
public:
    explicit InteractingItemInterface() {}
    virtual ~InteractingItemInterface() {}

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) = 0;
};

#endif // INTERACTINGITEMINTERFACE_H
