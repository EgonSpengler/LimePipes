/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "measure.h"

Measure::Measure(MusicItem *parent)
    : MusicItem(MusicItem::MeasureType, MusicItem::SymbolType, parent)
{
}
