/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Tune
  * A Tune represents a Score played by a specific instrument.
  */

#include "tune.h"

bool Tune::okToInsertChild(const MusicItem *item)
{
    const Symbol *symbol = symbolFromMusicItem(item);
    if (this->hasInstrument()) {
        if (symbol) {
            return instrument()->supportsSymbolType(symbol->symbolType());
        }
    }
    return false;
}

