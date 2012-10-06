/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PITCHDELEGATEINSTRUMENT_H
#define PITCHDELEGATEINSTRUMENT_H

#include <instrument.h>

class PitchDelegateInstrument : public Instrument
{
public:
    PitchDelegateInstrument()
        : Instrument(LP::BassDrum,
                     "PitchDelegateInstrument",
                     PitchContextPtr(new DelegatePitchContext())) {}
    bool supportsSymbolType(int type) const
        { Q_UNUSED(type) return true; }

private:
    class DelegatePitchContext : public PitchContext
    {
    public:
        explicit DelegatePitchContext()
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
};

#endif // PITCHDELEGATEINSTRUMENT_H
