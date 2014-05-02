/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTEINTERACTION_H
#define MELODYNOTEINTERACTION_H

#include <common/graphictypes/iteminteraction.h>

class MelodyNoteInteraction : public ItemInteraction
{
    Q_OBJECT
public:
    explicit MelodyNoteInteraction(QObject *parent = 0);

    void mousePressEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(const QGraphicsItem *item, QGraphicsSceneContextMenuEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setData(const QVariant &value, int role);

private:
    void handleAddDots();
    int m_dotCount;
};

#endif // MELODYNOTEINTERACTION_H
