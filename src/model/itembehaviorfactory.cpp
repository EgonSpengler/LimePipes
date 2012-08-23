/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "itembehaviorfactory.h"
#include <score.h>
#include <tune.h>
#include <symbol.h>

ItemBehaviorFactory::ItemBehaviorFactory()
{
}

ItemBehavior *ItemBehaviorFactory::getBehavior(ItemBehavior::Type type)
{
    switch(type)
    {
    case ItemBehavior::NoItem:
        qWarning( "NoItemType should not be used with ItemBehaviorFactory::getBehavior()" );
        return new ItemBehavior(ItemBehavior::NoItem, ItemBehavior::NoItem);
    case ItemBehavior::RootItem:
        return new ItemBehavior(ItemBehavior::RootItem, ItemBehavior::Score);
    case ItemBehavior::Score:
        return new Score();
    case ItemBehavior::Tune:
        return new Tune();
    case ItemBehavior::Symbol:
        return new Symbol();
    default:
        qWarning( "ItemBehavior %d is not supported by ItemBehaviorFactory", type);
        return new ItemBehavior(ItemBehavior::NoItem, ItemBehavior::NoItem);
    }
}
