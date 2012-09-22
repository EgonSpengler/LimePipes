/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "ghb_instrument.h"

bool GHB_Instrument::supportsSymbolType(int type) const
{
    switch (type) {

    case GHB::MelodyNote:
    case GHB::Doubling:
    case LP::Bar:
        return true;
    default:
        return false;
    }
}
