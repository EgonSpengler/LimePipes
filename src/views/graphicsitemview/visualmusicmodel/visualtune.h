/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALTUNE_H
#define VISUALTUNE_H

#include "abstractvisualitem.h"

class VisualTune : public AbstractVisualItem
{
public:
    explicit VisualTune();

    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // VISUALTUNE_H
