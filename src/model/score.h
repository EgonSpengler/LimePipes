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
#include <itemdatatypes.h>

class Score : public MusicItem
{
public:
    explicit Score()
        : MusicItem(MusicItem::ScoreType, MusicItem::TuneType) {}
    Score(const QString &title)
        : MusicItem(MusicItem::ScoreType, MusicItem::TuneType)
        { setData(title, LP::scoreTitle); }
};

#endif // SCORE_H
