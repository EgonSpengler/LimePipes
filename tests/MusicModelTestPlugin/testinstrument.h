/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTINSTRUMENT_H
#define TESTINSTRUMENT_H

#include <datatypes/instrument.h>

class TestInstrument : public Instrument
{
public:
    TestInstrument()
        : Instrument(LP::BassDrum,
                     "Testinstrument",
                     PitchContextPtr(new TestPitchContext())) {}

    bool supportsSymbolType(int type) const {
        Q_UNUSED(type)
        return true;
    }

private:
    class TestPitchContext : public PitchContext
    {
    public:
        explicit TestPitchContext()
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

#endif // TESTINSTRUMENT_H
