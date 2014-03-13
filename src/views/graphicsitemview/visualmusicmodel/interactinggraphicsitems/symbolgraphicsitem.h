/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICSITEM_H
#define SYMBOLGRAPHICSITEM_H

#include <common/defines.h>
#include "interactinggraphicsitem.h"

class SymbolGraphicsItem : public InteractingGraphicsItem
{
public:
    explicit SymbolGraphicsItem(QGraphicsItem *parent = 0);

    enum { Type = SymbolGraphicItem };
    int type() const { return Type; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // InteractingGraphicsItem interface
    void setData(const QVariant &value, int key);
};

#endif // SYMBOLGRAPHICSITEM_H
