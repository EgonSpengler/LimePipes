/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ITEMBEHAVIORFACTORY_H
#define ITEMBEHAVIORFACTORY_H

#include <itembehavior.h>

class ItemBehaviorFactory
{
public:
    ItemBehaviorFactory();
    static ItemBehavior *getBehavior(ItemBehavior::Type type);
};

#endif // ITEMBEHAVIORFACTORY_H
