/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MEASUREBEHAVIOR_H
#define MEASUREBEHAVIOR_H

#include "itembehavior.h"

class MeasureBehavior : public ItemBehavior
{
public:
    MeasureBehavior();

    // ItemBehavior interface
public:
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);
};

#endif // MEASUREBEHAVIOR_H
