/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "part.h"

Part::Part(MusicItem *parent)
    : MusicItem(MusicItem::PartType, MusicItem::MeasureType, parent)
{
}
