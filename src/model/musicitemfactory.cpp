/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicitemfactory.h"

#include <rootitem.h>
#include <score.h>
#include <tune.h>
#include <symbol.h>

MusicItem *MusicItemFactory::getMusicItem(MusicItem::Type type)
{
    switch(type)
    {
    case MusicItem::NoItem:
        qWarning( "NoItem type should not be used with MusicItemFactory::getMusicItem()" );
        return new MusicItem();
    case MusicItem::RootItem:
        return new RootItem();
    case MusicItem::Score:
        return new Score();
    case MusicItem::Tune:
        return new Tune();
    case MusicItem::Symbol:
        return new Symbol();
    default:
        qWarning( "ItemBehavior %d is not supported by ItemBehaviorFactory", type);
        return new MusicItem();
    }
}
