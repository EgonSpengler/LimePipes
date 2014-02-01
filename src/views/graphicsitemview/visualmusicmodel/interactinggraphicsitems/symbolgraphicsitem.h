/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICSITEM_H
#define SYMBOLGRAPHICSITEM_H

#include "interactinggraphicsitem.h"

class SymbolGraphicsItem : public InteractingGraphicsItem
{
public:
    explicit SymbolGraphicsItem(QGraphicsItem *parent = 0);
};

#endif // SYMBOLGRAPHICSITEM_H
