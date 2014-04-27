/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneContextMenuEvent>
#include "../iteminteraction.h"
#include "interactinggraphicsitem.h"

InteractingGraphicsItem::InteractingGraphicsItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_itemInteraction(0),
      m_interactionMode(Direct)
{
}

ItemInteraction *InteractingGraphicsItem::itemInteraction() const
{
    return m_itemInteraction;
}

void InteractingGraphicsItem::setData(const QVariant &value, int key)
{
    if (m_itemInteraction != 0) {
        m_itemInteraction->setData(value, key);
    }
}

void InteractingGraphicsItem::setItemInteraction(ItemInteraction *itemInteraction)
{
    if (itemInteraction == m_itemInteraction)
        return;

    if (m_itemInteraction)
        delete m_itemInteraction;

    itemInteraction->setParent(this);
    m_itemInteraction = itemInteraction;

    emit itemInteractionChanged();
}

void InteractingGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->mousePressEvent(event);
    }
}

void InteractingGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->mouseMoveEvent(event);
    }
}

void InteractingGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->mouseReleaseEvent(event);
    }
}

void InteractingGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->mouseDoubleClickEvent(event);
    }
}

void InteractingGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->contextMenuEvent(event);
    }
}

bool InteractingGraphicsItem::sceneEventFilter(QGraphicsItem *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if (!(m_interactionMode == Filter ||
            m_interactionMode == Both))
        return false; // Event will be delivered to watched item

    switch (event->type()) {
    case QEvent::GraphicsSceneHoverEnter:
        break;
    case QEvent::GraphicsSceneHoverMove:
        break;
    case QEvent::GraphicsSceneHoverLeave:
        break;
    case QEvent::GraphicsSceneDragEnter:
        break;
    case QEvent::GraphicsSceneDragMove:
        break;
    case QEvent::GraphicsSceneDragLeave:
        break;
    case QEvent::GraphicsSceneDrop:
        break;
    case QEvent::GraphicsSceneWheel:
        break;
    case QEvent::GraphicsSceneResize:
        break;
    case QEvent::GraphicsSceneMove:
        break;
    case QEvent::GraphicsSceneMousePress: {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (!mouseEvent)
            return false;
        m_itemInteraction->mousePressEvent(mouseEvent);
        return true;
    }
    case QEvent::GraphicsSceneMouseMove: {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (!mouseEvent)
            return false;
        m_itemInteraction->mouseMoveEvent(mouseEvent);
        return true;
    }
    case QEvent::GraphicsSceneMouseRelease: {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (!mouseEvent)
            return false;
        m_itemInteraction->mouseReleaseEvent(mouseEvent);
        return true;
    }
    case QEvent::GraphicsSceneMouseDoubleClick: {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (!mouseEvent)
            return false;
        m_itemInteraction->mouseDoubleClickEvent(mouseEvent);
        return true;
    }
    case QEvent::GraphicsSceneContextMenu: {
        QGraphicsSceneContextMenuEvent *contextMenuEvent = static_cast<QGraphicsSceneContextMenuEvent*>(event);
        if (!contextMenuEvent)
            return false;
        m_itemInteraction->contextMenuEvent(contextMenuEvent);
        return true;
    }
    default:
        return false;
    }

    return false;
}

InteractingGraphicsItem::InteractionMode InteractingGraphicsItem::interactionMode() const
{
    return m_interactionMode;
}

void InteractingGraphicsItem::setInteractionMode(const InteractionMode &interactionMode)
{
    m_interactionMode = interactionMode;
}


SMuFLPtr InteractingGraphicsItem::smufl() const
{
    return m_smufl;
}

void InteractingGraphicsItem::setSmufl(const SMuFLPtr &smufl)
{
    if (m_smufl == smufl)
        return;

    m_smufl = smufl;
    smuflHasChanged(m_smufl);
}

