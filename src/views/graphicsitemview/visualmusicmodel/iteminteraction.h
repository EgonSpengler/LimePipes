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
#include <itemdatatypes.h>

class QVariant;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneContextMenuEvent;

class ItemInteraction : public QObject
{
    Q_OBJECT
public:
    explicit ItemInteraction(QObject *parent = 0);
    virtual ~ItemInteraction() {}

    void setGraphicsScene(QGraphicsScene *scene)
    {
        m_graphicsScene = scene;
    }

    QGraphicsScene *graphicsScene() const
    {
        return m_graphicsScene;
    }

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)
    { Q_UNUSED(event); }

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    { Q_UNUSED(event); }

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    { Q_UNUSED(event); }

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    { Q_UNUSED(event); }

    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
    { Q_UNUSED(event); }

    virtual void setData(const QVariant& value, LP::ScoreDataRole role)
    { Q_UNUSED(value); Q_UNUSED(role); }

signals:
    void dataChanged(const QVariant& value, int role);

private:
    QGraphicsScene *m_graphicsScene;
};

#endif // ITEMINTERACTION_H
