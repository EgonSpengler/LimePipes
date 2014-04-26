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

class SymbolInteraction : public ItemInteraction
{
public:
    explicit SymbolInteraction(const SMuFLPtr& smufl, QObject *parent = 0);

    // ItemInteraction interface
public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void setData(const QVariant &value, int role);

private:
    qreal m_currentYDragStart;
    SMuFLPtr m_smufl;
    PitchContextPtr m_pitchContext;
    PitchPtr m_currentPitch;
};

#endif // SYMBOLINTERACTION_H
