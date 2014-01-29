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
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
}

StaffType StaffGraphicsItem::staffType() const
{
    return m_staffType;
}

void StaffGraphicsItem::setStaffType(StaffType type)
{
    m_staffType = type;
    setSizeHintsForStaffType(type);
}

int StaffGraphicsItem::lineHeight() const
{
    return m_lineHeight;
}

void StaffGraphicsItem::setLineHeight(qreal lineHeight)
{
    if (lineHeight < 1)
        return;

    m_lineHeight = lineHeight;
    setSizeHintsForStaffType(m_staffType);
}

int StaffGraphicsItem::lineWidth() const
{
    return m_lineWidth;
}

void StaffGraphicsItem::setLineWidth(qreal width)
{
    if (width < 1)
        return;

    m_lineWidth = width;
    setWindowFrameRectForLineWidth(m_lineWidth);
}

void StaffGraphicsItem::setSizeHintsForStaffType(StaffType type)
{
    if (type == StaffType::Standard) {
        qreal height = m_lineHeight * 5;
        QSizeF maximum(maximumSize());
        QSizeF minimum(minimumSize());
        setMaximumSize(maximum.width(), height);
        setMinimumSize(minimum.width(), height);
    }
}

void StaffGraphicsItem::setWindowFrameRectForLineWidth(qreal width)
{
    // Half of the line will be painted outside of rect
    width /= 2;
    setWindowFrameMargins(width, width, width, width);
}
