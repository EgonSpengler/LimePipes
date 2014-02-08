/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "graphicsviewzoom.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <QApplication>
#include <QScrollBar>
#include <qmath.h>

GraphicsViewZoom::GraphicsViewZoom(QGraphicsView* view)
    : QObject(view), m_graphicsView(view)
{
    m_graphicsView->viewport()->installEventFilter(this);
    m_graphicsView->setMouseTracking(true);
    m_modifiers = Qt::ControlModifier;
    m_zoomFactorBase = 1.0015;
}

void GraphicsViewZoom::gentleZoom(double factor) {
    m_graphicsView->scale(factor, factor);
    m_graphicsView->centerOn(m_targetScenePos);
    QPointF delta_viewport_pos = m_targetViewportPos - QPointF(m_graphicsView->viewport()->width() / 2.0,
                                                               m_graphicsView->viewport()->height() / 2.0);
    QPointF viewport_center = m_graphicsView->mapFromScene(m_targetScenePos) - delta_viewport_pos;
    m_graphicsView->centerOn(m_graphicsView->mapToScene(viewport_center.toPoint()));
    emit zoomed();
}

void GraphicsViewZoom::setModifiers(Qt::KeyboardModifiers modifiers) {
    m_modifiers = modifiers;

}

void GraphicsViewZoom::setZoomFactorBase(double value) {
    m_zoomFactorBase = value;
}

bool GraphicsViewZoom::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        QPointF delta = m_targetViewportPos - mouse_event->pos();
        if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
            m_targetViewportPos = mouse_event->pos();
            m_targetScenePos = m_graphicsView->mapToScene(mouse_event->pos());
        }
    } else if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
        if (QApplication::keyboardModifiers() == m_modifiers) {
            if (wheel_event->orientation() == Qt::Vertical) {
                double angle = wheel_event->angleDelta().y();
                double factor = qPow(m_zoomFactorBase, angle);
                gentleZoom(factor);
                return true;
            }
        }
    }
    Q_UNUSED(object)
    return false;
}
