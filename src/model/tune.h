/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNE_H
#define TUNE_H

#include <musicitem.h>
#include <symbol.h>
#include <itemdatatypes.h>
#include <datatypes/instrument.h>

class Tune : public MusicItem
{
public:
    explicit Tune()
        : MusicItem(MusicItem::TuneType, MusicItem::SymbolType) {}
    Tune(Instrument *instrument)
        : MusicItem(MusicItem::TuneType, MusicItem::SymbolType)
        { setInstrument(instrument); }

    void setInstrument(Instrument *instrument)
        { setData(QVariant::fromValue<Instrument*>(instrument), LP::tuneInstrument); }
    Instrument *instrument()
        { return data(LP::tuneInstrument).value<Instrument*>(); }
    bool okToInsertChild(const MusicItem *item);

private:
    bool hasInstrument()
        { return data(LP::tuneInstrument).isValid(); }
    const Symbol *symbolFromMusicItem(const MusicItem *item)
        { return static_cast<const Symbol*>(item); }
};

#endif // TUNE_H
