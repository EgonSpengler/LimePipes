/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALITEMINTERFACE_H
#define VISUALITEMINTERFACE_H

class QGraphicsSceneMouseEvent;

class VisualItemInterface
{
public:
    virtual ~VisualItemInterface() {}

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) = 0;
};

#endif // VISUALITEMINTERFACE_H
