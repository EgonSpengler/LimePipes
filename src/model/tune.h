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
    explicit Tune();
    explicit Tune(InstrumentPtr instrument);

    InstrumentPtr instrument() const { return data(LP::tuneInstrument).value<InstrumentPtr>(); }
    bool okToInsertChild(const MusicItem *item);
    bool itemSupportsWritingOfData(int role) const;

private:
    void setInstrument(InstrumentPtr instrument);
    const Symbol *symbolFromMusicItem(const MusicItem *item);
};

#endif // TUNE_H
