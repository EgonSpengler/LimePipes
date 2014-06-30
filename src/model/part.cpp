/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>
#include <common/datahandling/itembehavior.h>

#include "part.h"

Part::Part(MusicItem *parent)
    : MusicItem(MusicItem::PartType, MusicItem::MeasureType, parent)
{
    initItem();

    initData(QVariant::fromValue<bool>(false), LP::PartRepeat);
}

void Part::setStaffType(StaffType staffType)
{
    initItem();

    initData(QVariant::fromValue<StaffType>(staffType), LP::PartStaffType);
}

void Part::setClefType(ClefType clef)
{
    initItem();

    initData(QVariant::fromValue<ClefType>(clef), LP::PartClefType);
}

void Part::initItem()
{
    ItemBehavior *behavior = new ItemBehavior();
    setItemBehavior(behavior);
}

bool Part::itemSupportsWritingOfData(int role) const
{
    if (LP::allPartDataRoles.contains(static_cast<LP::PartDataRole>(role)))
        return true;
    return false;
}

void Part::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
}

void Part::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
}
