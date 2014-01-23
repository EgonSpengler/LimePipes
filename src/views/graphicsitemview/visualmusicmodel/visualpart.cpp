/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <itemdatatypes.h>
#include "interactinggraphicsitems/staffgraphicsitem.h"
#include "visualpart.h"

VisualPart::VisualPart(QObject *parent)
    : VisualItem(VisualItem::VisualPartItem,
                 VisualItem::GraphicalRowType,
                 parent),
      m_repeat(false),
      m_staffType(StaffType::None)
{
    appendStaff();
}

void VisualPart::setRepeat(bool repeat)
{
    m_repeat = repeat;
}

bool VisualPart::repeat() const
{
    return m_repeat;
}

void VisualPart::setStaffType(StaffType staffType)
{
    m_staffType = staffType;
    foreach (StaffGraphicsItem *staffItem, m_staffItems) {
        staffItem->setStaffType(staffType);
    }
}

StaffType VisualPart::staffType() const
{
    return m_staffType;
}

int VisualPart::staffCount() const
{
    return m_staffItems.count();
}

void VisualPart::appendStaff()
{
    m_staffItems.append(new StaffGraphicsItem());
    emit rowSequenceChanged();
}

void VisualPart::removeLastStaff()
{
    if (m_staffItems.count() < 2)
        return;

    StaffGraphicsItem *staff = m_staffItems.takeLast();
    delete staff;

    emit rowSequenceChanged();
}

void VisualPart::setData(const QVariant &value, int key)
{
    switch (key) {
    case LP::PartRepeat: {
        setRepeat(value.toBool());
        break;
    }
    case LP::PartStaffType: {
        setStaffType(value.value<StaffType>());
        break;
    }
    }
}

void VisualPart::insertChildItem(int index, VisualItem *childItem)
{
}
