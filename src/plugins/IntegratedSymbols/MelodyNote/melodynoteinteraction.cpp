/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "melodynoteinteraction.h"
#include "../integratedsymbolsdefines.h"
#include <QKeyEvent>
#include <QDebug>

MelodyNoteInteraction::MelodyNoteInteraction(QObject *parent) :
    ItemInteraction(parent),
    m_dotCount(0)
{
}

void MelodyNoteInteraction::mousePressEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
}

void MelodyNoteInteraction::mouseMoveEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
}

void MelodyNoteInteraction::mouseReleaseEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
}

void MelodyNoteInteraction::mouseDoubleClickEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
}

void MelodyNoteInteraction::contextMenuEvent(const QGraphicsItem *item, QGraphicsSceneContextMenuEvent *event)
{
}

void MelodyNoteInteraction::setData(const QVariant &value, int role)
{
    if (role == LP::MelodyNoteDots) {
        m_dotCount = value.toInt();
    }
}

void MelodyNoteInteraction::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Period:
        handleAddDots();
        break;
    default:
        break;
    }
}

void MelodyNoteInteraction::handleAddDots()
{
    int dots = m_dotCount;
    dots++;

    if (dots > MelodyNoteMaxDots)
        dots = 0;

    emit dataChanged(dots, LP::MelodyNoteDots);
}
