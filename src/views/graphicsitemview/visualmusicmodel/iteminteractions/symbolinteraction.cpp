/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QGraphicsSceneMouseEvent>
#include "symbolinteraction.h"
#include <QDebug>

SymbolInteraction::SymbolInteraction(const SMuFLPtr &smufl, QObject *parent)
    : ItemInteraction(parent),
      m_smufl(smufl)
{
}

void SymbolInteraction::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_smufl.isNull())
        return;

    m_currentYDragStart = event->pos().y();
    qDebug() << QString("Mouse press at y %1").arg(m_currentYDragStart);
}

void SymbolInteraction::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal halfStaffSpace = m_smufl->font().pixelSize() / 4 / 8;
    qreal currentYPos = event->pos().y();
    qDebug() << QString("Mouse move at y %1").arg(currentYPos);
}

void SymbolInteraction::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("mouse release");
}

void SymbolInteraction::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("mouse doubleclick");
}

void SymbolInteraction::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    qDebug("context menu event");
}

void SymbolInteraction::setData(const QVariant &value, int role)
{
    if (role == LP::SymbolPitch) {
        PitchPtr pitch = value.value<PitchPtr>();
        m_currentPitch = pitch;
    }
    if (role == LP::SymbolPitchContext) {
        PitchContextPtr pitchContext = value.value<PitchContextPtr>();
        m_pitchContext = pitchContext;
    }
}
