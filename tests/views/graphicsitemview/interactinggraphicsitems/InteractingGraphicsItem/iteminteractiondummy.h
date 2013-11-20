/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INTERACTINGITEMDUMMY_H
#define INTERACTINGITEMDUMMY_H

#include <QObject>
#include <views/graphicsitemview/iteminteraction.h>

class ItemInteractionDummy : public ItemInteraction
{
    Q_OBJECT
public:
    explicit ItemInteractionDummy(QObject *parent = 0);

signals:
    void mousePressEventTriggered();
    void mouseMoveEventTriggered();
    void mouseReleaseEventTriggered();
    void mouseDoubleClickEventTriggered();
    void contextMenuEventTriggered();

    // VisualItemInterface interface
public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        emit mousePressEventTriggered();
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        emit mouseMoveEventTriggered();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        emit mouseReleaseEventTriggered();
    }

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {
        emit mouseDoubleClickEventTriggered();
    }

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
    {
        emit contextMenuEventTriggered();
    }
};

#endif // INTERACTINGITEMDUMMY_H
