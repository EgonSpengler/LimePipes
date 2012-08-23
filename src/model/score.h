/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include "itembehavior.h"

class Score : public ItemBehavior
{
public:
    explicit Score()
        : ItemBehavior(ItemBehavior::Score, ItemBehavior::Tune) {}
};

#endif // SCORE_H
