/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QJsonObject>

#include <common/itemdataroles.h>

#include "datakeys.h"
#include "scorebehavior.h"

ScoreBehavior::ScoreBehavior()
    : ItemBehavior(LP::ItemType::ScoreType)
{
}

QJsonObject ScoreBehavior::toJson() const
{
    QJsonObject json(ItemBehavior::toJson());
    insertScoreData(json, LP::ScoreTitle, DataKey::ScoreTitle);
    insertScoreData(json, LP::ScoreComposer, DataKey::ScoreComposer);
    insertScoreData(json, LP::ScoreArranger, DataKey::ScoreArranger);
    insertScoreData(json, LP::ScoreYear, DataKey::ScoreYear);
    insertScoreData(json, LP::ScoreCopyright, DataKey::ScoreCopyright);
    insertScoreData(json, LP::ScoreType, DataKey::ScoreType);

    return json;
}

void ScoreBehavior::fromJson(const QJsonObject &json)
{
    ItemBehavior::fromJson(json);
}

void ScoreBehavior::insertScoreData(QJsonObject &json, int dataRole, const QString &key) const
{
    QString scoreData = data(dataRole).toString();
    if (!scoreData.isEmpty())
        json.insert(key, scoreData);
}
