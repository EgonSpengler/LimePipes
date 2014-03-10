/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>
#include <common/datatypes/instrument.h>
#include <symbol.h>
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

bool Measure::okToInsertChild(const MusicItem *item, int row)
{
    Q_UNUSED(row);

    MusicItem *part = parent();
    if (!part) return false;

    MusicItem *tune = part->parent();
    if (!tune) return false;

    QVariant instrumentVar = tune->data(LP::TuneInstrument);
    if (!instrumentVar.isValid() || !instrumentVar.canConvert<InstrumentPtr>())
        return false;

    const Symbol *symbol = static_cast<const Symbol*>(item);
    if (!symbol) return false;

    InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
    return instrument->supportsSymbolType(symbol->symbolType());
}
