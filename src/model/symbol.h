/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include "itembehavior.h"

class Symbol : public ItemBehavior
{
public:
    explicit Symbol()
        : ItemBehavior(ItemBehavior::SymbolType, ItemBehavior::NoItemType) {}
};

#endif // SYMBOL_H
