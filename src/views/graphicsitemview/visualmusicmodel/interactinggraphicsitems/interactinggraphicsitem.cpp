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

#include <common/graphictypes/iteminteraction.h>
#include <common/layoutsettings.h>

#include "interactinggraphicsitem.h"

InteractingGraphicsItem::HoverMode InteractingGraphicsItem::s_hoverMode =
        InteractingGraphicsItem::NoHoverMode;

InteractingGraphicsItem::InteractingGraphicsItem(QGraphicsItem *parent)
    : QGraphicsWidget(parent),
      m_itemInteraction(0),
      m_interactionMode(Direct)
{
    setAcceptHoverEvents(true);
    setMusicFont(LayoutSettings::musicFont());
    connect(LayoutSettings::musicFont().data(), &MusicFont::fontChanged,
            [this] {
        setMusicFont(LayoutSettings::musicFont());
    });
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

    if (m_itemInteraction) {
        m_itemInteraction->deleteLater();
        m_itemInteraction = 0;
    }

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
        m_itemInteraction->mousePressEvent(this, event);
    }
}

void InteractingGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->mouseMoveEvent(this, event);
    }
}

void InteractingGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->mouseReleaseEvent(this, event);
    }
}

void InteractingGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->mouseDoubleClickEvent(this, event);
    }
}

void InteractingGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug() << "InteractionGraphicsItem: Hover enter mode: " << static_cast<int>(s_hoverMode);
    QGraphicsWidget::hoverEnterEvent(event);
}

void InteractingGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsWidget::hoverMoveEvent(event);
}

void InteractingGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsWidget::hoverLeaveEvent(event);
}

/*!
 * \brief InteractingGraphicsItem::focusInEvent
 * focusInEvent is always handled by this class itself. If there are child items,
 * theses should set this item as focus proxy.
 * \param event
 */
void InteractingGraphicsItem::focusInEvent(QFocusEvent *event)
{
    if (!m_itemInteraction)
        return;

    m_itemInteraction->focusInEvent(this, event);
}

/*!
 * \brief InteractingGraphicsItem::focusOutEvent
 * focusOutEvent is always handled by this class itself. If there are child items,
 * theses should set this item as focus proxy.
 * \param event
 */
void InteractingGraphicsItem::focusOutEvent(QFocusEvent *event)
{
    if (!m_itemInteraction)
        return;

    m_itemInteraction->focusOutEvent(this, event);
}

/*!
 * \brief InteractingGraphicsItem::keyPressEvent
 * keyPressEvent is always handled by this class itself. If there are child items,
 * theses should set this item as focus proxy.
 * \param event
 */
void InteractingGraphicsItem::keyPressEvent(QKeyEvent *event)
{
    if (!m_itemInteraction)
        return;

    m_itemInteraction->keyPressEvent(this, event);
}

void InteractingGraphicsItem::keyReleaseEvent(QKeyEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->keyReleaseEvent(this, event);
    }
}

void InteractingGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (!m_itemInteraction)
        return;

    if (m_interactionMode == Direct ||
            m_interactionMode == Both) {
        m_itemInteraction->contextMenuEvent(this, event);
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
        m_itemInteraction->mousePressEvent(watched, mouseEvent);
        return true;
    }
    case QEvent::GraphicsSceneMouseMove: {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (!mouseEvent)
            return false;
        m_itemInteraction->mouseMoveEvent(watched, mouseEvent);
        return true;
    }
    case QEvent::GraphicsSceneMouseRelease: {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (!mouseEvent)
            return false;
        m_itemInteraction->mouseReleaseEvent(watched, mouseEvent);
        return true;
    }
    case QEvent::GraphicsSceneMouseDoubleClick: {
        QGraphicsSceneMouseEvent *mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
        if (!mouseEvent)
            return false;
        m_itemInteraction->mouseDoubleClickEvent(watched, mouseEvent);
        return true;
    }
    case QEvent::GraphicsSceneContextMenu: {
        QGraphicsSceneContextMenuEvent *contextMenuEvent = static_cast<QGraphicsSceneContextMenuEvent*>(event);
        if (!contextMenuEvent)
            return false;
        m_itemInteraction->contextMenuEvent(watched, contextMenuEvent);
        return true;
    }
    case QEvent::KeyPress: {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (!keyEvent)
            return false;
        m_itemInteraction->keyPressEvent(watched, keyEvent);
        return true;
    }
    case QEvent::KeyRelease: {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (!keyEvent)
            return false;
        m_itemInteraction->keyReleaseEvent(watched, keyEvent);
        return true;
    }
    case QEvent::FocusIn: {
        QFocusEvent *focusEvent = static_cast<QFocusEvent*>(event);
        if (!focusEvent)
            return false;
        m_itemInteraction->focusInEvent(watched, focusEvent);
        return true;
    }
    case QEvent::FocusOut: {
        QFocusEvent *focusEvent = static_cast<QFocusEvent*>(event);
        if (!focusEvent)
            return false;
        m_itemInteraction->focusOutEvent(watched, focusEvent);
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

MusicFontPtr InteractingGraphicsItem::musicFont() const
{
    return m_musicFont;
}

void InteractingGraphicsItem::setMusicFont(const MusicFontPtr &musicFont)
{
    m_musicFont = musicFont;
    musicFontHasChanged(m_musicFont);
}
