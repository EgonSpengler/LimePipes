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
    case MusicItem::NoItemType:
        qWarning( "NoItem type should not be used with MusicItemFactory::getMusicItem()" );
        return new EmptyMusicItem();
    case MusicItem::RootItemType:
        return new RootItem();
    case MusicItem::ScoreType:
        return new Score();
    case MusicItem::TuneType:
        return new Tune();
    case MusicItem::SymbolType:
        return new Symbol();
    default:
        qWarning( "ItemBehavior %d is not supported by ItemBehaviorFactory", type);
        return new EmptyMusicItem();
    }
}
