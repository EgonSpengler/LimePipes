/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef STAFFGRAPHICSITEM_H
#define STAFFGRAPHICSITEM_H

#include <common/defines.h>
#include "interactinggraphicsitem.h"

class StaffGraphicsItem : public InteractingGraphicsItem
{
    friend class StaffGraphicsItemTest;

public:
    explicit StaffGraphicsItem(QGraphicsItem *parent = 0);

    StaffType staffType() const;
    void setStaffType(StaffType type);

    int lineHeight() const;
    void setLineHeight(qreal lineHeight);

    int lineWidth() const;
    void setLineWidth(qreal width);

private:
    void setSizeHintsForStaffType(StaffType type);
    void setWindowFrameRectForLineWidth(qreal width);
    StaffType m_staffType;
    qreal m_lineHeight;
    qreal m_lineWidth;
};

#endif // STAFFGRAPHICSITEM_H
