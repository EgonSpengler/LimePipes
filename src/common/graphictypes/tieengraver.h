/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIEENGRAVER_H
#define TIEENGRAVER_H

#include "baseengraver.h"

class TieEngraver : public BaseEngraver
{
public:
    TieEngraver();

    // BaseEngraver interface
public:
    void insertGraphicsBuilder(int index, SymbolGraphicBuilder *builder);
    void removeGraphicsBuilder(SymbolGraphicBuilder *builder);
};

#endif // TIEENGRAVER_H
