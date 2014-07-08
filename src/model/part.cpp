/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>
#include <common/datahandling/partbehavior.h>

#include "part.h"

using namespace LP;

Part::Part(MusicItem *parent)
    : MusicItem(ItemType::PartType, ItemType::MeasureType, parent)
{
    initItem();

    initData(QVariant::fromValue<bool>(false), LP::PartRepeat);
}

void Part::setStaffType(StaffType staffType)
{
    initData(QVariant::fromValue<StaffType>(staffType), LP::PartStaffType);
}

void Part::setClefType(ClefType clef)
{
    initData(QVariant::fromValue<ClefType>(clef), LP::PartClefType);
}

void Part::initItem()
{
    ItemBehavior *behavior = new PartBehavior();
    setItemBehavior(behavior);
}

bool Part::itemSupportsWritingOfData(int role) const
{
    if (LP::allPartDataRoles.contains(static_cast<LP::PartDataRole>(role)))
        return true;
    return false;
}
