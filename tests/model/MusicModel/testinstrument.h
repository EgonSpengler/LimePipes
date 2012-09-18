/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTINSTRUMENT_H
#define TESTINSTRUMENT_H

#include <instrument.h>

class TestInstrument : public Instrument
{
public:
    static int notOkToInsertSymbolType;
    TestInstrument()
        : Instrument(LP::BassDrum, "Bass drum") {}

    bool supportsSymbolType(int type) const {
        if (type == notOkToInsertSymbolType) {
            return false;
        }
        return true;
    }
};

#endif // TESTINSTRUMENT_H
