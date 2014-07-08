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
#include <common/datahandling/tunebehavior.h>

#include "tune.h"

using namespace LP;

Tune::Tune(MusicItem *parent)
    : MusicItem(ItemType::TuneType, ItemType::PartType, parent)
{
    initItem();

    setInstrument(LP::NoInstrument);
    initData(QVariant::fromValue<TimeSignature>(TimeSignature(TimeSignature::_4_4)),
                                                LP::TuneTimeSignature);
}

Tune::Tune(int instrumentType, MusicItem *parent)
    : MusicItem(ItemType::TuneType, ItemType::PartType, parent)
{
    initItem();

    setInstrument(instrumentType);
    initData(QVariant::fromValue<TimeSignature>(TimeSignature(TimeSignature::_4_4)),
                                                LP::TuneTimeSignature);
}

void Tune::initItem()
{
    ItemBehavior *behavior = new TuneBehavior();
    setItemBehavior(behavior);
}

void Tune::setInstrument(int instrumentType)
{
    initData(instrumentType, LP::TuneInstrument);
}

bool Tune::itemSupportsWritingOfData(int role) const
{
    if (role == LP::TuneInstrument)
        return false;

    if (LP::allTuneDataRoles.contains(static_cast<LP::TuneDataRole>(role)))
        return true;

    return false;
}
