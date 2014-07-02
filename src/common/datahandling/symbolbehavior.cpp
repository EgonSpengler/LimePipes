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

#include "symbolbehavior.h"

SymbolBehavior::SymbolBehavior()
    : ItemBehavior(LP::ItemType::Symbol)
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
    setData(QVariant(), LP::SymbolPitchContext);
    setData(QVariant(), LP::SymbolLength);

    m_options = options;

    if (options.testFlag(HasPitch)) {
        setData(QVariant::fromValue<Pitch>(Pitch()), LP::SymbolPitch);
    }
    if (options.testFlag(HasLength)) {
        setData(QVariant::fromValue<Length::Value>(Length::_8), LP::SymbolLength);
    }
}

bool SymbolBehavior::hasOption(SymbolBehavior::SymbolOption option)
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
