/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GREATHIGHLANDBAGPIPEINSTRUMENT_H
#define GREATHIGHLANDBAGPIPEINSTRUMENT_H

#include <instrument.h>
#include <ghb_symboltypes.h>

class GHB_PitchContext : public PitchContext
{
public:
    explicit GHB_PitchContext()
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
};

class GHB_Instrument : public Instrument
{
public:
    GHB_Instrument()
        : Instrument(LP::GreatHighlandBagpipe,
                     QString("Great Highland Bagpipe"),
                     PitchContextPtr(new GHB_PitchContext())) {}
    bool supportsSymbolType(int type) const;
};

#endif // GREATHIGHLANDBAGPIPEINSTRUMENT_H
