/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QJsonObject>

#include <common/itemdataroles.h>
#include <common/datahandling/datakeys.h>

#include "melodynotebehavior.h"

MelodyNoteBehavior::MelodyNoteBehavior()
{
    setSymbolType(LP::MelodyNote);
    setSupportedData(QList<int>({LP::MelodyNoteDots}));
    setOptions(SymbolBehavior::HasLength | SymbolBehavior::HasPitch);
}

QJsonObject MelodyNoteBehavior::toJson() const
{
    QJsonObject json(SymbolBehavior::toJson());

    int dots = data(LP::MelodyNoteDots).toInt();
    if (dots) {
        json.insert(DataKey::MelodyNoteDots, dots);
    }

    return json;
}

void MelodyNoteBehavior::fromJson(const QJsonObject &json)
{
    SymbolBehavior::fromJson(json);

    int dots = json.value(DataKey::MelodyNoteDots).toInt();
    if (dots) {
        setData(dots, LP::MelodyNoteDots);
    }
}
