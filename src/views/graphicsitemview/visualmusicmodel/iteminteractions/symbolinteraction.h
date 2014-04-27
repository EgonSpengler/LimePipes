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
#include <common/graphictypes/SMuFL/smufl.h>
#include <common/datatypes/pitchcontext.h>
#include <QHash>
#include <QPair>

class SymbolInteraction : public ItemInteraction
{
public:
    explicit SymbolInteraction(const SMuFLPtr& smufl, QObject *parent = 0);

    // ItemInteraction interface
public:
    void mousePressEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(const QGraphicsItem *item, QGraphicsSceneContextMenuEvent *event);
    void setData(const QVariant &value, int role);

private:
    void setPitchDragAreas();
    int pitchPosForYPos(qreal yPos);
    QPointF staffPointForSymbolPoint(const QGraphicsItem *symbolItem, const QPointF &point) const;
    qreal m_currentYDragStart;
    SMuFLPtr m_smufl;
    PitchContextPtr m_pitchContext;
    PitchPtr m_currentPitch;
    QHash<int, QPair<qreal, qreal>> m_pitchDragAreas;
};

#endif // SYMBOLINTERACTION_H
