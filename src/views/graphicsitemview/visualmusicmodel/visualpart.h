/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALPART_H
#define VISUALPART_H

#include <QVector>
#include <common/graphictypes/SMuFL/smufl.h>
#include <common/defines.h>
#include "visualitem.h"

class StaffGraphicsItem;

class VisualPart : public VisualItem
{
    friend class VisualPartTest;

public:
    explicit VisualPart(QObject *parent = 0);

    void setRepeat(bool repeat);
    bool repeat() const;

    void setStaffType(StaffType staffType);
    StaffType staffType() const;

    int staffCount() const;
    void appendStaff();
    void removeLastStaff();

    // VisualItem interface
    void setData(const QVariant &value, int key);
    void insertChildItem(int index, VisualItem *childItem);

    SMuFLPtr smufl() const;
    void setSmufl(const SMuFLPtr &smufl);

private:
    StaffGraphicsItem *newStaffItem();
    QVector<StaffGraphicsItem*> m_staffItems;
    bool m_repeat;
    StaffType m_staffType;
    SMuFLPtr m_smufl;
};

#endif // VISUALPART_H
