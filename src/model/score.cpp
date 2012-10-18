/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Score
  * A Score represents a container for one or more @ref Tune "Tunes" and has at least a title.
  */

#include "score.h"

Score::Score()
    : MusicItem(MusicItem::ScoreType, MusicItem::TuneType)
{
}

Score::Score(const QString &title)
    : MusicItem(MusicItem::ScoreType, MusicItem::TuneType)
{
    setTitle(title);
}

void Score::setTitle(const QString &title)
{
    setData(title, LP::scoreTitle);
}

bool Score::itemSupportsWritingOfData(int role) const
{
    switch (role) {
    case LP::scoreArranger:
    case LP::scoreComposer:
    case LP::scoreCopyright:
    case LP::scoreTimeSignature:
    case LP::scoreTitle:
    case LP::scoreYear:
        return true;
    default:
        return false;
    }
}
