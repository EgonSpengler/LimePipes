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

#include <QXmlStreamWriter>
#include <common/datatypes/timesignature.h>

#include "tune.h"

void Tune::setInstrument(InstrumentPtr instrument)
{
    m_data.insert(LP::TuneInstrument, QVariant::fromValue<InstrumentPtr>(instrument));
}

Tune::Tune(MusicItem *parent)
    : MusicItem(MusicItem::TuneType, MusicItem::PartType, parent)
{
    setInstrument(InstrumentPtr(new NullInstrument()));
    initData(QVariant::fromValue<TimeSignature>(TimeSignature(TimeSignature::_4_4)),
                                                LP::TuneTimeSignature);
}

Tune::Tune(InstrumentPtr instrument, MusicItem *parent)
    : MusicItem(MusicItem::TuneType, MusicItem::PartType, parent)
{
    setInstrument(instrument);
}

bool Tune::itemSupportsWritingOfData(int role) const
{
    if (role == LP::TuneInstrument)
        return false;

    if (LP::allTuneDataRoles.contains(static_cast<LP::TuneDataRole>(role)))
        return true;

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
