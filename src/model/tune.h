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
    explicit Tune(int instrumentType, MusicItem *parent = 0);

    int instrument() const { return data(LP::TuneInstrument).toInt(); }
    void setInstrument(int instrumentType);

    bool itemSupportsWritingOfData(int role) const;
    void writeItemDataToXmlStream(QXmlStreamWriter *writer);
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader);

private:
    void initItem();
};

#endif // TUNE_H
