/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Tune
  * A Tune represents a Score played by a specific instrument.
  */

#include "tune.h"
#include <QXmlStreamWriter>
#include <symbols/barline.h>

void Tune::setInstrument(InstrumentPtr instrument)
{
    m_data.insert(LP::tuneInstrument, QVariant::fromValue<InstrumentPtr>(instrument));
}

Tune::Tune(MusicItem *parent)
    : MusicItem(MusicItem::TuneType, MusicItem::PartType, parent)
{
    setInstrument(InstrumentPtr(new NullInstrument()));
}

Tune::Tune(InstrumentPtr instrument)
    : MusicItem(MusicItem::TuneType, MusicItem::PartType)
{
    setInstrument(instrument);
}

bool Tune::itemSupportsWritingOfData(int role) const
{
    Q_UNUSED(role)
    return false;
}

void Tune::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
    Q_UNUSED(writer)
}

void Tune::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
    Q_UNUSED(reader)
}
