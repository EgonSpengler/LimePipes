/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "greathighlandbagpipeinstrument.h"

bool GreatHighlandBagpipeInstrument::supportsSymbolType(int type) const
{
    switch (type) {

    case LP::MelodyNote:
    case LP::Bar:
        return true;

    default:
        return false;
    }
}
