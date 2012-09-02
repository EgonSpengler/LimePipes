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

class GreatHighlandBagpipeInstrument : public Instrument
{
public:
    GreatHighlandBagpipeInstrument()
        : Instrument(LP::GreatHighlandBagpipe, QString("Great Highland Bagpipe")) {}
    bool supportsSymbolType(int type) const;
};

#endif // GREATHIGHLANDBAGPIPEINSTRUMENT_H
