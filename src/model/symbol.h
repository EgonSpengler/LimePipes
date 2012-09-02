/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include <musicitem.h>
#include <itemdatatypes.h>
#include "../interfaces/interfaceglobals.h"

class Symbol : public MusicItem
{
public:
    explicit Symbol()
        : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
        { setData(LP::NoSymbolType, LP::symbolType);}
    Symbol(int type)
        : MusicItem(MusicItem::SymbolType, MusicItem::NoItemType)
        { setData(type, LP::symbolType); }
    int symbolType() const
        { return data(LP::symbolType).toInt(); }
};

#endif // SYMBOL_H
