/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PARTBEHAVIOR_H
#define PARTBEHAVIOR_H

#include "itembehavior.h"

class PartBehavior : public ItemBehavior
{
public:
    PartBehavior();

    // ItemBehavior interface
public:
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);
};

#endif // PARTBEHAVIOR_H
