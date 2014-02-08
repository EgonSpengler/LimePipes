/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICSVIEWZOOM_H
#define GRAPHICSVIEWZOOM_H

#include <QObject>
#include <QPointF>

class QGraphicsView;

class GraphicsViewZoom : public QObject {
    Q_OBJECT
public:
    GraphicsViewZoom(QGraphicsView* view);
    void gentleZoom(double factor);
    void setModifiers(Qt::KeyboardModifiers modifiers);
    void setZoomFactorBase(double value);

signals:
    void zoomed();

private:
    bool eventFilter(QObject* object, QEvent* event);

    QGraphicsView* m_graphicsView;
    Qt::KeyboardModifiers m_modifiers;
    double m_zoomFactorBase;
    QPointF m_targetScenePos;
    QPointF m_targetViewportPos;
};

#endif // GRAPHICSVIEWZOOM_H
