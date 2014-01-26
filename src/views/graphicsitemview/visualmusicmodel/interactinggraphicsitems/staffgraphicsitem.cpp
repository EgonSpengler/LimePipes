/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "staffgraphicsitem.h"

StaffGraphicsItem::StaffGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_staffType(StaffType::None),
      m_lineHeight(0),
      m_lineWidth(1)
{
}

StaffType StaffGraphicsItem::staffType() const
{
    return m_staffType;
}

void StaffGraphicsItem::setStaffType(StaffType type)
{
    m_staffType = type;
}

int StaffGraphicsItem::lineHeight() const
{
    return m_lineHeight;
}

void StaffGraphicsItem::setLineHeight(int lineHeight)
{
    if (lineHeight < 1)
        return;

    m_lineHeight = lineHeight;
}

int StaffGraphicsItem::lineWidth() const
{
    return m_lineWidth;
}

void StaffGraphicsItem::setLineWidth(int width)
{
    if (width < 1)
        return;

    m_lineWidth = width;
}
