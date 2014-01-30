/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include "staffgraphicsitem.h"

StaffGraphicsItem::StaffGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_staffType(StaffType::None),
      m_lineHeight(0)
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

qreal StaffGraphicsItem::lineWidth() const
{
    return m_pen.widthF();
}

void StaffGraphicsItem::setLineWidth(qreal width)
{
    if (width < 1)
        return;

    m_pen.setWidthF(width);
    setWindowFrameRectForLineWidth(width);
}

void StaffGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_staffType == StaffType::Standard) {
        qreal width = geometry().width();
        qreal height = geometry().height();
        painter->setPen(m_pen);
        painter->drawRect(0, 0, width, height);
        for (int i = 1; i < 4; ++i) {
            painter->drawLine(0, i*m_lineHeight, width, i*m_lineHeight);
        }
    }
}

void StaffGraphicsItem::setSizeHintsForStaffType(StaffType type)
{
    if (type == StaffType::Standard) {
        qreal height = m_lineHeight * 4;
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
