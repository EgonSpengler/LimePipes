/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICITEMFACTORY_H
#define MUSICITEMFACTORY_H

#include <musicitem.h>

class MusicItemFactory
{
public:
    MusicItemFactory() {}
    static MusicItem *getMusicItem(MusicItem::Type type);
};

#endif // MUSICITEMFACTORY_H
