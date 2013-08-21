/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALSYMBOL_H
#define VISUALSYMBOL_H

#include "abstractvisualitem.h"

class VisualSymbol : public AbstractVisualItem
{
public:
    explicit VisualSymbol();

    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // VISUALSYMBOL_H
