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

#include <QXmlStreamWriter>

#include <common/datahandling/scorebehavior.h>

#include "score.h"

using namespace LP;

Score::Score(MusicItem *parent)
    : MusicItem(ItemType::ScoreType, ItemType::TuneType, parent)
{
    initItem();
}

Score::Score(const QString &title)
    : MusicItem(ItemType::ScoreType, ItemType::TuneType)
{
    initItem();
    setTitle(title);
}

void Score::initItem()
{
    ItemBehavior *behavior = new ScoreBehavior();
    setItemBehavior(behavior);
}

void Score::setTitle(const QString &title)
{
    setData(title, LP::ScoreTitle);
}

bool Score::itemSupportsWritingOfData(int role) const
{
    if (LP::allScoreDataRoles.contains(static_cast<LP::ScoreDataRole>(role)))
        return true;

    return false;
}
