/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "ghb_instrument.h"

GHB_PitchContext::GHB_PitchContext()
    : PitchContext()
{
    insertPitch(0, "F");
    insertPitch(1, "E");
    insertPitch(2, "D");
    insertPitch(3, "C");
    insertPitch(4, "B");
    insertPitch(5, "Low A");
    insertPitch(-1, "High G");
    insertPitch(-2, "High A");
    insertPitch(6, "Low G");
}

GHB_Instrument::GHB_Instrument()
    : Instrument(LP::GreatHighlandBagpipe,
                 QString("Great Highland Bagpipe"),
                 PitchContextPtr(new GHB_PitchContext()))
{
}

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

