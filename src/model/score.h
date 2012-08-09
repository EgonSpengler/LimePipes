/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORE_H
#define SCORE_H

#include "musicitem.h"
#include "model_itemtypes.h"

class Score : public MusicItem
{
public:
    explicit Score();
    int type() const { return ScoreType; }
};

#endif // SHEETMUSIC_H
