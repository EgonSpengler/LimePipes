/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "symbolinteraction.h"

SymbolInteraction::SymbolInteraction(QObject *parent)
    : ItemInteraction(parent)
{
}

void SymbolInteraction::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("mouse press");
}

void SymbolInteraction::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug("mouse move");
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
}
