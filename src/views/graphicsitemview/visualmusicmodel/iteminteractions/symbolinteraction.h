/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLINTERACTION_H
#define SYMBOLINTERACTION_H

#include "../iteminteraction.h"

class SymbolInteraction : public ItemInteraction
{
public:
    explicit SymbolInteraction(QObject *parent = 0);

    // ItemInteraction interface
public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void setData(const QVariant &value, int role);
};

#endif // SYMBOLINTERACTION_H
