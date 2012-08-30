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

class Symbol : public MusicItem
{
public:
    explicit Symbol()
        : MusicItem(MusicItem::Symbol, MusicItem::NoItem) {}
};

#endif // SYMBOL_H
