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
    qDebug() << QString("Mouse press at y %1").arg(m_currentYDragStart);
}

void SymbolInteraction::setPitchDragAreas()
{
    if (m_smufl.isNull())
        return;

    qreal halfStaffSpace = m_smufl->font().pixelSize() / 4 / 2;
    for (int i = m_pitchContext->highestStaffPos();
         i <= m_pitchContext->lowestStaffPos(); ++i) {
        qreal staffPosition = i * halfStaffSpace;
        qreal upperBound = staffPosition - halfStaffSpace / 2;
        qreal lowerBound = staffPosition + halfStaffSpace / 2;
//        qDebug() << "Staff position " << i << ", upper: " << upperBound << ", lower: " << lowerBound;
        m_pitchDragAreas.insert(i, qMakePair(upperBound, lowerBound));
    }
}

int SymbolInteraction::pitchPosForYPos(qreal yPos)
{

}

QPointF SymbolInteraction::staffPointForSymbolPoint(const QGraphicsItem *symbolItem, const QPointF &point) const
{
    if (!symbolItem->parentItem())
        return point;

    return symbolItem->mapToItem(symbolItem->parentItem()->parentItem(), point);
}

void SymbolInteraction::mouseMoveEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    QPointF staffEventPos = staffPointForSymbolPoint(item, event->pos());
    qDebug() << "Staff pos: " << staffEventPos;
//    foreach ()
//    qreal currentYPos = event->pos();


//    qreal quarterStaffSpace = m_smufl->font().pixelSize() / 4 / 4;
//    qreal currentDragDistance = currentYPos - m_currentYDragStart;

//    // Check moving direction
//    // and if a pitch change is necessary
//    bool movingUpwards = false;
//    if (currentDragDistance < 0) { // upwards
//        currentDragDistance *= -1;
//        movingUpwards = true;
//    }

//    qreal pitchChangeCount = (currentDragDistance  - quarterStaffSpace) / quarterStaffSpace * 2;
//    qDebug() << "Pitch Change count: " << pitchChangeCount;

//    int currentPitchStaffPos = m_currentPitch->staffPos();
//    int nextPitchStaffPos = currentPitchStaffPos;
//    if (movingUpwards) {
//        int highestStaffPos = m_pitchContext->highestStaffPos();
//        nextPitchStaffPos -= pitchChangeCount;
//        if (nextPitchStaffPos < highestStaffPos) {
//            nextPitchStaffPos = highestStaffPos;
//        }
//    } else {
//        int lowestStaffPos = m_pitchContext->lowestStaffPos();
//        nextPitchStaffPos += pitchChangeCount;
//        if (nextPitchStaffPos > lowestStaffPos) {
//            nextPitchStaffPos = lowestStaffPos;
//        }
//    }

//    if (nextPitchStaffPos == currentPitchStaffPos)
//        return;

//    PitchPtr pitch = m_pitchContext->pitchForStaffPos(nextPitchStaffPos);
//    m_currentPitch = pitch;
//    QVariant pitchData = QVariant::fromValue<PitchPtr>(pitch);
//    emit dataChanged(pitchData, LP::SymbolPitch);

//    qDebug() << QString("Mouse move at y %1").arg(currentYPos);
//    qDebug() << QString("Drag distance: %1").arg(currentYPos - m_currentYDragStart);
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
