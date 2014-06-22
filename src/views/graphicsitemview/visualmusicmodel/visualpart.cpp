/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>
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
    StaffGraphicsItem *staffItem = newStaffItem();
    m_staffItems.append(staffItem);
    appendRow(staffItem);
}

StaffGraphicsItem *VisualPart::newStaffItem()
{
    StaffGraphicsItem *staffItem = new StaffGraphicsItem;
    staffItem->setStaffType(staffType());
    staffItem->setClefType(cleffType());

    return staffItem;
}

ClefType VisualPart::cleffType() const
{
    return m_cleffType;
}

void VisualPart::setCleffType(const ClefType &cleffType)
{
    m_cleffType = cleffType;
    foreach (StaffGraphicsItem *staffItem, m_staffItems) {
        staffItem->setClefType(cleffType);
    }
}

void VisualPart::removeLastStaff()
{
    if (m_staffItems.count() < 2)
        return;

    StaffGraphicsItem *staff = m_staffItems.takeLast();
    removeLastRow();
    delete staff;
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
    case LP::PartClefType: {
        setCleffType(value.value<ClefType>());
        break;
    }
    }
}

void VisualPart::insertChildItem(int index, VisualItem *childItem)
{
    if (m_staffItems.isEmpty())
        return;

    InteractingGraphicsItem *graphicsItem = childItem->inlineGraphic();
    if (!graphicsItem)
        return;

    StaffGraphicsItem *lastStaffItem = m_staffItems.last();
    if (lastStaffItem->measureCount() >= 4) {
        appendStaff();
        lastStaffItem = m_staffItems.last();
    }

    lastStaffItem->insertChildItem(index, graphicsItem);
}
