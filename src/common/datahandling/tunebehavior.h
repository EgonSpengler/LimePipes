/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNEBEHAVIOR_H
#define TUNEBEHAVIOR_H

#include "itembehavior.h"

class TuneBehavior : public ItemBehavior
{
public:
    TuneBehavior();

    // ItemBehavior interface
public:
    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);
};

#endif // TUNEBEHAVIOR_H
