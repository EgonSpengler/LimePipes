/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNE_H
#define TUNE_H

#include <musicitem.h>

class Tune : public MusicItem
{
public:
    explicit Tune()
        : MusicItem(MusicItem::Tune, MusicItem::Symbol) {}
};

#endif // TUNE_H
