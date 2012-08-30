/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include <musicitem.h>

class Score : public MusicItem
{
public:
    explicit Score()
        : MusicItem(MusicItem::Score, MusicItem::Tune) {}
};

#endif // SCORE_H
