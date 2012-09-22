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

class GHB_Instrument : public Instrument
{
public:
    GHB_Instrument()
        : Instrument(LP::GreatHighlandBagpipe, QString("Great Highland Bagpipe")) {}
    bool supportsSymbolType(int type) const;
};

#endif // GREATHIGHLANDBAGPIPEINSTRUMENT_H
