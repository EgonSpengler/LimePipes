/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QSizePolicy>
#include <QPen>
#include <QPainter>
#include <QGraphicsLinearLayout>
#include <QGraphicsLayoutItem>
#include <QGraphicsItem>

#include <common/layoutsettings.h>
#include "staffgraphicsitem.h"
#include <QDebug>

namespace {
const int InitialLineHeight = 8;
const int InitialLineWidth  = 1;
}

StaffGraphicsItem::StaffGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_staffType(StaffType::None),
      m_staffSpace(0),
      m_topMargin(0),
      m_measureLayout(0),
      m_clefGlyph(0)
{
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

    m_measureLayout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    m_measureLayout->setSpacing(0);
    m_measureLayout->setContentsMargins(0, 0, 0, 0);

    musicFontHasChanged(LayoutSettings::musicFont());

    updateMarginsToMusicLayout();
    connect(LayoutSettings::musicLayout().data(), &MusicLayout::layoutChanged,
            [this] {
        updateMarginsToMusicLayout();
    });

    m_clefGlyph = new ClefGlyphItem(ClefType::Treble, this);
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
    return m_staffSpace;
}

void StaffGraphicsItem::setStaffSpace(qreal lineHeight)
{
    if (lineHeight < 1)
        return;

    m_staffSpace = lineHeight;
    setSizeHintsForStaffType(m_staffType);
}

qreal StaffGraphicsItem::penWidth() const
{
    return m_pen.widthF();
}

void StaffGraphicsItem::setPenWidth(qreal width)
{
    m_pen.setWidthF(width);
    setWindowFrameRectForLineWidth(width);
    setSizeHintsForStaffType(m_staffType);
}

void StaffGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_staffType == StaffType::Standard) {
        if (contentsRect().height() != m_staffSpace * 4) {
            qWarning() << "StaffGraphicsItem: Contents rect has wrong height";
        }

        qreal width = contentsRect().width();
        painter->setPen(m_pen);
        qreal contentTop = contentsRect().top();
        for (int i = 0; i < 5; ++i) {
            painter->drawLine(0, i*m_staffSpace + contentTop,
                              width, i*m_staffSpace + contentTop);
        }
    }
//    QPen pen(Qt::darkGreen);
//    pen.setWidthF(1.0);
//    painter->setPen(pen);
//    painter->drawRect(boundingRect());

//    pen = QPen(Qt::red);
//    pen.setWidthF(1.0);
//    painter->setPen(pen);
//    painter->drawRect(contentsRect());

//    pen = QPen(Qt::green);
//    pen.setWidthF(1.0);
//    painter->setPen(pen);
//    painter->drawRect(m_measureLayout->geometry());
}

void StaffGraphicsItem::setSizeHintsForStaffType(StaffType type)
{
    qreal top, right, bottom, left;
    if (type == StaffType::Standard) {
        qreal height = m_staffSpace * 4;
        getContentsMargins(&left, &top, &right, &bottom);
        height += top;
        QSizeF maximum(maximumSize());
        QSizeF minimum(minimumSize());
        setMaximumSize(maximum.width(), height);
        setMinimumSize(minimum.width(), height);
    }
}

void StaffGraphicsItem::setWindowFrameRectForLineWidth(qreal width)
{
    width /= 2;

    // Half of the line will be painted outside of rect
    setWindowFrameMargins(width, width, width, width);
}

void StaffGraphicsItem::updateMarginsToMusicLayout()
{
    qreal staffSpace = LayoutSettings::musicFont()->staffSpace();
    m_topMargin = LayoutSettings::musicLayout()->spaceAboveStaff();
    m_topMargin *= staffSpace;
    // TODO Fix size
    setContentsMargins(0, m_topMargin, 0, 0);
    setSizeHintsForStaffType(m_staffType);

    qDebug() << "StaffGraphicsItem: Window frame rect: " << windowFrameRect();
}

void StaffGraphicsItem::layoutClef()
{
    m_clefGlyph->setY(contentsRect().top() + m_clefGlyph->yOffset());
}

ClefType StaffGraphicsItem::clefType() const
{
    return m_clefGlyph->clef();
}

void StaffGraphicsItem::setClefType(const ClefType &clefType)
{
    m_clefGlyph->setClef(clefType);
    layoutClef();
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
    setStaffSpace(staffSpace);
    Engravings engravings(musicFont->engravings());
    qreal width = engravings.staffLineThickness * staffSpace;
    setPenWidth(width);
}
