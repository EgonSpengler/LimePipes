/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QSizePolicy>
#include <QPainter>
#include <QGraphicsLinearLayout>
#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include "staffgraphicsitem.h"
#include <QDebug>

namespace {
const int InitialLineHeight = 8;
const int InitialLineWidth  = 1;
}

StaffGraphicsItem::StaffGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_staffType(StaffType::None),
      m_staffLineHeight(0),
      m_measureLayout(0)
{
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

    m_measureLayout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    m_measureLayout->setSpacing(0);
    m_measureLayout->setContentsMargins(0, 0, 0, 0);

    setStaffLineHeight(InitialLineHeight);
    setPenWidth(InitialLineWidth);
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

int StaffGraphicsItem::staffLineHeight() const
{
    return m_staffLineHeight;
}

void StaffGraphicsItem::setStaffLineHeight(qreal lineHeight)
{
    if (lineHeight < 1)
        return;

    m_staffLineHeight = lineHeight;
    setSizeHintsForStaffType(m_staffType);
}

qreal StaffGraphicsItem::penWidth() const
{
    return m_pen.widthF();
}

void StaffGraphicsItem::setPenWidth(qreal width)
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
        painter->setPen(m_pen);
        for (int i = 0; i < 5; ++i) {
            painter->drawLine(0, i*m_staffLineHeight, width, i*m_staffLineHeight);
        }
    }
}

void StaffGraphicsItem::setSizeHintsForStaffType(StaffType type)
{
    if (type == StaffType::Standard) {
        qreal height = m_staffLineHeight * 4;
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

void StaffGraphicsItem::insertChildItem(int index, InteractingGraphicsItem *childItem)
{
    m_measureLayout->insertItem(index, childItem);
    setFixedWidthsOnChildren();
}

void StaffGraphicsItem::setFixedWidthsOnChildren()
{
    int childCount = m_measureLayout->count();
    qreal childWidth = geometry().width() / childCount;

    for (int i = 0; i < childCount; ++i) {
        QGraphicsLayoutItem *childItem = m_measureLayout->itemAt(i);

        if (childItem->minimumWidth() == childWidth &&
                childItem->maximumWidth() == childWidth) {
            continue;
        }

        childItem->setMinimumWidth(childWidth);
        childItem->setMaximumWidth(childWidth);
    }
}

int StaffGraphicsItem::measureCount() const
{
    return m_measureLayout->count();
}

void StaffGraphicsItem::musicFontHasChanged(const MusicFontPtr &musicFont)
{
    qreal staffSpace = musicFont->staffSpace();
    setStaffLineHeight(staffSpace);
    Engravings engravings(musicFont->engravings());
    qreal width = engravings.staffLineThickness * staffSpace;
    setPenWidth(width);
}
