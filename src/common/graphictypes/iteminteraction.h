/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ITEMINTERACTION_H
#define ITEMINTERACTION_H

#include <QObject>
#include <common/itemdataroles.h>

class QVariant;
class QGraphicsItem;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneContextMenuEvent;
class QKeyEvent;

class ItemInteraction : public QObject
{
    Q_OBJECT
public:
    explicit ItemInteraction(QObject *parent = 0);
    virtual ~ItemInteraction() {}

    virtual void mousePressEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
    { Q_UNUSED(event); }

    virtual void mouseMoveEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
    { Q_UNUSED(event); }

    virtual void mouseReleaseEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
    { Q_UNUSED(event); }

    virtual void mouseDoubleClickEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
    { Q_UNUSED(event); }

    virtual void keyPressEvent(QKeyEvent *event)
    { Q_UNUSED(event); }

    virtual void keyReleaseEvent(QKeyEvent *event)
    { Q_UNUSED(event); }

    virtual void contextMenuEvent(const QGraphicsItem *item, QGraphicsSceneContextMenuEvent *event)
    { Q_UNUSED(event); }

    virtual void setData(const QVariant& value, int role)
    { Q_UNUSED(value); Q_UNUSED(role); }

signals:
    void dataChanged(const QVariant& value, int role);
};

#endif // ITEMINTERACTION_H
