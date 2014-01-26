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
    void setLineHeight(int lineHeight);

    int lineWidth() const;
    void setLineWidth(int width);

private:
    StaffType m_staffType;
    int m_lineHeight;
    int m_lineWidth;
};

#endif // STAFFGRAPHICSITEM_H
