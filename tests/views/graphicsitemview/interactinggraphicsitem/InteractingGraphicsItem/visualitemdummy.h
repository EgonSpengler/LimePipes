#ifndef VISUALITEMDUMMY_H
#define VISUALITEMDUMMY_H

#include <QObject>
#include <views/graphicsitemview/visualiteminterface.h>

class VisualItemDummy : public QObject,
                        public VisualItemInterface
{
    Q_OBJECT
public:
    explicit VisualItemDummy(QObject *parent = 0);

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

#endif // VISUALITEMDUMMY_H
