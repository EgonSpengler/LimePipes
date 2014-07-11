/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "ghb_symboltypes.h"
#include "doublingbehavior.h"

DoublingBehavior::DoublingBehavior()
{
    setSymbolType(GHB::Doubling);
}

QJsonObject DoublingBehavior::toJson() const
{
    QJsonObject json(SymbolBehavior::toJson());

    return json;
}

void DoublingBehavior::fromJson(const QJsonObject &json)
{
    SymbolBehavior::fromJson(json);
}
