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
        : MusicItem(MusicItem::TuneType, MusicItem::SymbolType)
        { setInstrument(new Instrument()); }
    Tune(Instrument *instrument)
        : MusicItem(MusicItem::TuneType, MusicItem::SymbolType)
        { setInstrument(instrument); }
    QVariant data(int role) const;
    void setData(const QVariant &value, int role);

    void setInstrument(Instrument *instrument);
    Instrument *instrument() const
        { return data(LP::tuneInstrument).value<Instrument*>(); }
    bool okToInsertChild(const MusicItem *item);

private:
    bool hasInstrument()
        { return data(LP::tuneInstrument).isValid(); }
    const Symbol *symbolFromMusicItem(const MusicItem *item)
        { return static_cast<const Symbol*>(item); }
    void setDisplayRole(QString &name);
};

#endif // TUNE_H
