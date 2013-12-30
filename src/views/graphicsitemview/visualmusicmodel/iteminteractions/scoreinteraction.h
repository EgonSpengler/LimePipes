/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREINTERACTION_H
#define SCOREINTERACTION_H

#include <itemdatatypes.h>
#include "../iteminteraction.h"

class ScorePropertiesDialog;

class ScoreInteraction : public ItemInteraction
{
    friend class ScoreInteractionTest;

public:
    explicit ScoreInteraction(QObject *parent = 0);
    ~ScoreInteraction();

    // InteractingItemInterface interface
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void setData(const QVariant &value, int role);

private slots:
    void propertyTextChanged(LP::ScoreDataRole dataRole, const QString& text);

private:
    void createConnections();
    ScorePropertiesDialog *m_scorePropertiesDialog;
};

#endif // SCOREINTERACTION_H
