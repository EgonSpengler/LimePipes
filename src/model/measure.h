/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MEASURE_H
#define MEASURE_H

#include <musicitem.h>

class Measure : public MusicItem
{
public:
    explicit Measure(MusicItem *parent=0);

    bool itemSupportsWritingOfData(int role) const;
    void writeItemDataToXmlStream(QXmlStreamWriter *writer);
    void readCurrentElementFromXmlStream(QXmlStreamReader *reader);
    bool okToInsertChild(const MusicItem *item, int row);
};

#endif // MEASURE_H
