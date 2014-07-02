/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QJsonObject>

#include <common/itemdataroles.h>
#include <common/datatypes/timesignature.h>

#include "datakeys.h"
#include "tunebehavior.h"

TuneBehavior::TuneBehavior()
    : ItemBehavior(LP::ItemType::Tune)
{
}

QJsonObject TuneBehavior::toJson() const
{
    QJsonObject json;
    int instrumentType = data(LP::TuneInstrument).toInt();
    if (instrumentType != LP::NoInstrument)
        json.insert(DataKey::InstrumentKey, instrumentType);

    TimeSignature timeSig = data(LP::TuneTimeSignature).value<TimeSignature>();
    if (timeSig.isValid()) {
        json.insert(DataKey::TimeSignatureKey, static_cast<int>(timeSig.type()));
    }

    return json;
}

void TuneBehavior::fromJson(const QJsonObject &json)
{
}
