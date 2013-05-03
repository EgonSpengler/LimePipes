/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "measure.h"

Measure::Measure(MusicItem *parent)
    : MusicItem(MusicItem::MeasureType, MusicItem::SymbolType, parent)
{
}

bool Measure::itemSupportsWritingOfData(int role) const
{
    return false;
}

void Measure::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
}

void Measure::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
}
