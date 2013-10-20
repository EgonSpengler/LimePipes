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
#include <views/graphicsitemview/interactingiteminterface.h>

class InteractingItemDummy : public QObject,
                             public InteractingItemInterface
{
    Q_OBJECT
public:
    explicit InteractingItemDummy(QObject *parent = 0);

signals:
    void mousePressEventTriggered();
    void mouseMoveEventTriggered();
    void mouseReleaseEventTriggered();
    void mouseDoubleClickEventTriggered();

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
};

#endif // INTERACTINGITEMDUMMY_H
