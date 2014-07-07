/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>
#include <common/datatypes/timesignature.h>

#include "datakeys.h"
#include "measurebehavior.h"

MeasureBehavior::MeasureBehavior()
    : ItemBehavior(LP::ItemType::MeasureType)
{
}

QJsonObject MeasureBehavior::toJson() const
{
    QJsonObject json(ItemBehavior::toJson());
    TimeSignature timeSig = data(LP::TuneTimeSignature).value<TimeSignature>();
    if (timeSig.isValid()) {
        json.insert(DataKey::TimeSignatureKey, static_cast<int>(timeSig.type()));
    }
    QVariant isUpbeatData = data(LP::MeasureIsUpbeat);
    if (isUpbeatData.isValid()) {
        json.insert(DataKey::MeasureIsUpbeat, isUpbeatData.toBool());
    }

    return json;
}

void MeasureBehavior::fromJson(const QJsonObject &json)
{
}
