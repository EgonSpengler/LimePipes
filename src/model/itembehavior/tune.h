/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TUNE_H
#define TUNE_H

#include "itembehavior.h"

class Tune : public ItemBehavior
{
public:
    explicit Tune()
        : ItemBehavior(ItemBehavior::Tune, ItemBehavior::Symbol) {}
};

#endif // TUNE_H
