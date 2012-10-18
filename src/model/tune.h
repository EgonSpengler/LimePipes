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
#include <interfaces/instrumentinterface.h>

class Tune : public MusicItem
{
public:
    explicit Tune()
        : MusicItem(MusicItem::TuneType, MusicItem::SymbolType)
        { setInstrument(InstrumentPtr(new NullInstrument())); }
    explicit Tune(InstrumentPtr instrument)
        : MusicItem(MusicItem::TuneType, MusicItem::SymbolType)
        { setInstrument(instrument); }

    InstrumentPtr instrument() const
        { return data(LP::tuneInstrument).value<InstrumentPtr>(); }
    bool okToInsertChild(const MusicItem *item);
    bool itemSupportsWritingOfData(int role) const;

private:
    void setInstrument(InstrumentPtr instrument);
    const Symbol *symbolFromMusicItem(const MusicItem *item)
        { return static_cast<const Symbol*>(item); }
};

#endif // TUNE_H
