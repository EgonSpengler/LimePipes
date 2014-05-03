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

SymbolInteraction::SymbolInteraction(const MusicFontPtr &musicFont, QObject *parent)
    : ItemInteraction(parent),
      m_musicFont(musicFont),
      m_interaction(0)
{
}

void SymbolInteraction::setAdditionalInteraction(ItemInteraction *interaction)
{
    if (interaction == 0)
        return;

    if (m_interaction != 0) {
        m_interaction->deleteLater();
        m_interaction = 0;
    }

    m_interaction = interaction;
    m_interaction->setParent(this);
    connect(m_interaction, &ItemInteraction::dataChanged,
            this, &ItemInteraction::dataChanged);
}

void SymbolInteraction::mousePressEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    if (m_musicFont.isNull())
        return;

    m_currentYDragStart = event->pos().y();
    setPitchDragAreas();

    if (m_interaction) {
        m_interaction->mousePressEvent(item, event);
    }
}

void SymbolInteraction::setPitchDragAreas()
{
    if (m_musicFont.isNull())
        return;

    qreal halfStaffSpace = m_musicFont->halfStaffSpace();
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

    if (m_interaction) {
        m_interaction->mouseMoveEvent(item, event);
    }
}

void SymbolInteraction::mouseReleaseEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    qDebug("mouse release");
    if (m_interaction) {
        m_interaction->mouseReleaseEvent(item, event);
    }
}

void SymbolInteraction::mouseDoubleClickEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    qDebug("mouse doubleclick");
    if (m_interaction) {
        m_interaction->mouseDoubleClickEvent(item, event);
    }
}

void SymbolInteraction::contextMenuEvent(const QGraphicsItem *item, QGraphicsSceneContextMenuEvent *event)
{
    qDebug("context menu event");
    if (m_interaction) {
        m_interaction->contextMenuEvent(item, event);
    }
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

    if (m_interaction) {
        m_interaction->setData(value, role);
    }
}

void SymbolInteraction::keyPressEvent(const QGraphicsItem *item, QKeyEvent *event)
{
    if (m_interaction) {
        m_interaction->keyPressEvent(item, event);
    }
}

void SymbolInteraction::keyReleaseEvent(const QGraphicsItem *item, QKeyEvent *event)
{
    if (m_interaction) {
        m_interaction->keyReleaseEvent(item, event);
    }
}


void SymbolInteraction::focusInEvent(const QGraphicsItem *item, QFocusEvent *event)
{
    qDebug("Symbol interaction focus in");
    if (m_interaction) {
        m_interaction->focusInEvent(item, event);
    }
}

void SymbolInteraction::focusOutEvent(const QGraphicsItem *item, QFocusEvent *event)
{
    qDebug("Symbol interaction focus out");
    if (m_interaction) {
        m_interaction->focusOutEvent(item, event);
    }
}
