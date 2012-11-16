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
    explicit Tune(MusicItem *parent=0);
    explicit Tune(InstrumentPtr instrument);

    InstrumentPtr instrument() const { return data(LP::tuneInstrument).value<InstrumentPtr>(); }
    void setInstrument(InstrumentPtr instrument);

    int startRowOfPart(int partNumber);

    bool okToInsertChild(const MusicItem *item, int row);

    bool itemSupportsWritingOfData(int role) const;
    void writeItemDataToXmlStream(QXmlStreamWriter *writer);
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader);

private:
    int findStartOfPart(int partNumber);
    bool rowIsPrecededByStartOfPart(int row);
    const Symbol *symbolFromMusicItem(const MusicItem *item);
};

#endif // TUNE_H
