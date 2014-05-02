/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "symbolinteraction.h"
#include <QDebug>

SymbolInteraction::SymbolInteraction(const SMuFLPtr &smufl, QObject *parent)
    : ItemInteraction(parent),
      m_smufl(smufl)
{
}

void SymbolInteraction::mousePressEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    if (m_smufl.isNull())
        return;

    m_currentYDragStart = event->pos().y();
    setPitchDragAreas();
}

void SymbolInteraction::setPitchDragAreas()
{
    if (m_smufl.isNull())
        return;

    qreal halfStaffSpace = m_smufl->halfStaffSpace();
    for (int i = m_pitchContext->highestStaffPos();
         i <= m_pitchContext->lowestStaffPos(); ++i) {
        qreal staffPosition = i * halfStaffSpace;
        qreal upperBound = staffPosition - halfStaffSpace / 2;
        qreal lowerBound = staffPosition + halfStaffSpace / 2;
        m_pitchDragAreas.insert(i, qMakePair(upperBound, lowerBound));
    }
}

QPointF SymbolInteraction::staffPointForSymbolPoint(const QGraphicsItem *symbolItem, const QPointF &point) const
{
    if (!symbolItem->parentItem())
        return point;

    return symbolItem->mapToItem(symbolItem->parentItem()->parentItem(), point);
}

int SymbolInteraction::pitchPosForStaffYPos(qreal yPos)
{
    foreach (int staffPos, m_pitchDragAreas.keys()) {
        QPair<qreal, qreal> dragArea = m_pitchDragAreas.value(staffPos);
        if (yPos > dragArea.first &&
                yPos < dragArea.second) {
            return staffPos;
        }
    }

    return 0;
}

void SymbolInteraction::mouseMoveEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    QPointF staffEventPos = staffPointForSymbolPoint(item, event->pos());
    int highestStaffPos = m_pitchContext->highestStaffPos();
    int lowestStaffPos = m_pitchContext->lowestStaffPos();
    qreal upperBound = m_pitchDragAreas.value(highestStaffPos).first;
    qreal lowerBound = m_pitchDragAreas.value(lowestStaffPos).second;
    int pitchStaffPos = 0;
    if (staffEventPos.y() < upperBound) {
        pitchStaffPos = highestStaffPos;
    } else if (staffEventPos.y() > lowerBound) {
        pitchStaffPos = lowestStaffPos;
    } else {
        pitchStaffPos = pitchPosForStaffYPos(staffEventPos.y());
    }

    PitchPtr pitch = m_pitchContext->pitchForStaffPos(pitchStaffPos);
    emit dataChanged(QVariant::fromValue<PitchPtr>(pitch), LP::SymbolPitch);
}

void SymbolInteraction::mouseReleaseEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    qDebug("mouse release");
}

void SymbolInteraction::mouseDoubleClickEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    qDebug("mouse doubleclick");
}

void SymbolInteraction::contextMenuEvent(const QGraphicsItem *item, QGraphicsSceneContextMenuEvent *event)
{
    qDebug("context menu event");
}

void SymbolInteraction::setData(const QVariant &value, int role)
{
    if (role == LP::SymbolPitch) {
        PitchPtr pitch = value.value<PitchPtr>();
        if (m_currentPitch == pitch)
            return;

        m_currentPitch = pitch;
    }
    if (role == LP::SymbolPitchContext) {
        PitchContextPtr pitchContext = value.value<PitchContextPtr>();
        m_pitchContext = pitchContext;
    }
}
