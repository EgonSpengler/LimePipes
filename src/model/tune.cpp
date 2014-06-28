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

Tune::Tune(MusicItem *parent)
    : MusicItem(MusicItem::TuneType, MusicItem::PartType, parent)
{
    setInstrument(LP::NoInstrument);
    initData(QVariant::fromValue<TimeSignature>(TimeSignature(TimeSignature::_4_4)),
                                                LP::TuneTimeSignature);
}

Tune::Tune(int instrumentType, MusicItem *parent)
    : MusicItem(MusicItem::TuneType, MusicItem::PartType, parent)
{
    setInstrument(instrumentType);
    initData(QVariant::fromValue<TimeSignature>(TimeSignature(TimeSignature::_4_4)),
                                                LP::TuneTimeSignature);
}

void Tune::setInstrument(int instrumentType)
{
    m_data.insert(LP::TuneInstrument, instrumentType);
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
