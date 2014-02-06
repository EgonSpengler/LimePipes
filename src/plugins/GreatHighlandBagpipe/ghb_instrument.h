/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GREATHIGHLANDBAGPIPEINSTRUMENT_H
#define GREATHIGHLANDBAGPIPEINSTRUMENT_H

#include <common/datatypes/instrument.h>
#include "ghb_symboltypes.h"

class GHB_PitchContext : public PitchContext
{
public:
    explicit GHB_PitchContext();
};

class GHB_Instrument : public Instrument
{
public:
    GHB_Instrument();

    bool supportsSymbolType(int type) const;
};

#endif // GREATHIGHLANDBAGPIPEINSTRUMENT_H
