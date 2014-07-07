/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>
#include <common/datatypes/pitch.h>
#include <common/datatypes/length.h>

#include "datakeys.h"
#include "symbolbehavior.h"

SymbolBehavior::SymbolBehavior()
    : ItemBehavior(LP::ItemType::SymbolType)
{
}

QJsonObject SymbolBehavior::toJson() const
{
    QJsonObject json(ItemBehavior::toJson());
    int symbolType = data(LP::SymbolType).toInt();
    if (symbolType != LP::NoSymbolType) {
        json.insert(DataKey::SymbolType, symbolType);
    }
    json.insert(DataKey::InstrumentKey, data(LP::SymbolInstrument).toInt());
    json.insert(DataKey::SymbolName, data(LP::SymbolName).toString());
    if (hasOption(HasLength)) {
        Length::Value length = data(LP::SymbolLength).value<Length::Value>();
        json.insert(DataKey::Lenght, static_cast<int>(length));
    }
    if (hasOption(HasPitch)) {
        Pitch pitch = data(LP::SymbolPitch).value<Pitch>();
        json.insert(DataKey::Pitch, pitch.toJson());
    }
    int spanType = data(LP::SymbolSpanType).toInt();
    if (spanType != 0) {
        json.insert(DataKey::SymbolSpanType, spanType);
    }

    return json;
}

void SymbolBehavior::fromJson(const QJsonObject &json)
{
}

SymbolBehavior::SymbolOptions SymbolBehavior::options() const
{
    return m_options;
}

void SymbolBehavior::setOptions(const SymbolOptions &options)
{
    // Unset all data
    setData(QVariant(), LP::SymbolPitch);
    setData(QVariant(), LP::SymbolLength);

    m_options = options;

    if (options.testFlag(HasPitch)) {
        setData(QVariant::fromValue<Pitch>(Pitch()), LP::SymbolPitch);
    }
    if (options.testFlag(HasLength)) {
        setData(QVariant::fromValue<Length::Value>(Length::_8), LP::SymbolLength);
    }
}

bool SymbolBehavior::hasOption(SymbolBehavior::SymbolOption option) const
{
    return m_options.testFlag(option);
}

int SymbolBehavior::symbolType() const
{
    return data(LP::SymbolType).toInt();
}

void SymbolBehavior::setSymbolType(int type)
{
    setData(QVariant(type), LP::SymbolType);
}
