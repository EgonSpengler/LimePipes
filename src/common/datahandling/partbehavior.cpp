/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>

#include "datakeys.h"
#include "partbehavior.h"

PartBehavior::PartBehavior()
    : ItemBehavior(LP::ItemType::Part)
{
}

QJsonObject PartBehavior::toJson() const
{
    QJsonObject json(ItemBehavior::toJson());
    StaffType staffType = data(LP::PartStaffType).value<StaffType>();
    json.insert(DataKey::StaffType, static_cast<int>(staffType));
    json.insert(DataKey::PartRepeat, data(LP::PartRepeat).toBool());
    ClefType clef = data(LP::PartClefType).value<ClefType>();
    json.insert(DataKey::ClefType, static_cast<int>(clef));

    return json;
}

void PartBehavior::fromJson(const QJsonObject &json)
{
}
