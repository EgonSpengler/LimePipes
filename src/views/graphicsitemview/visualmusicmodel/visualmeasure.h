/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALMEASURE_H
#define VISUALMEASURE_H

#include "abstractvisualitem.h"

class VisualMeasure : public AbstractVisualItem
{
public:
    explicit VisualMeasure();

    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // VISUALMEASURE_H
