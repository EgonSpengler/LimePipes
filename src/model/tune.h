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
#include <common/itemdataroles.h>
#include <common/datatypes/instrument.h>

class Tune : public MusicItem
{
public:
    explicit Tune(MusicItem *parent=0);
    explicit Tune(InstrumentPtr instrument);

    InstrumentPtr instrument() const { return data(LP::TuneInstrument).value<InstrumentPtr>(); }
    void setInstrument(InstrumentPtr instrument);

    int startRowOfPart(int partNumber);

    bool itemSupportsWritingOfData(int role) const;
    void writeItemDataToXmlStream(QXmlStreamWriter *writer);
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader);
};

#endif // TUNE_H
