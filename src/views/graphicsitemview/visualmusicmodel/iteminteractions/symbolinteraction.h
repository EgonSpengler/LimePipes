/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLINTERACTION_H
#define SYMBOLINTERACTION_H

#include <common/graphictypes/iteminteraction.h>
#include <common/graphictypes/MusicFont/musicfont.h>
#include <common/datatypes/pitchcontext.h>
#include <QHash>
#include <QPair>

class SymbolInteraction : public ItemInteraction
{
public:
    explicit SymbolInteraction(const MusicFontPtr& musicFont, QObject *parent = 0);

    void setAdditionalInteraction(ItemInteraction *interaction);

    // ItemInteraction interface
    void mousePressEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(const QGraphicsItem *item, QGraphicsSceneContextMenuEvent *event);
    void keyPressEvent(const QGraphicsItem *item, QKeyEvent *event);
    void keyReleaseEvent(const QGraphicsItem *item, QKeyEvent *event);
    void focusInEvent(const QGraphicsItem *item, QFocusEvent *event);
    void focusOutEvent(const QGraphicsItem *item, QFocusEvent *event);
    void setData(const QVariant &value, int role);
    void setPluginManager(const PluginManager &pluginManager);

private:
    void setPitchDragAreas();
    int pitchPosForStaffYPos(qreal yPos);
    QPointF staffPointForSymbolPoint(const QGraphicsItem *symbolItem, const QPointF &point) const;
    qreal m_currentYDragStart;
    MusicFontPtr m_musicFont;
    PitchContextPtr m_pitchContext;
    Pitch m_currentPitch;
    QHash<int, QPair<qreal, qreal>> m_pitchDragAreas;
    ItemInteraction *m_interaction;
    PluginManager m_pluginManager;
};

#endif // SYMBOLINTERACTION_H
