/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>

#include "part.h"

Part::Part(MusicItem *parent)
    : MusicItem(MusicItem::PartType, MusicItem::MeasureType, parent)
{
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
