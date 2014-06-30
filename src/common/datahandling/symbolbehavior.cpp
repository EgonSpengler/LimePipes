/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>

#include "symbolbehavior.h"

SymbolBehavior::SymbolBehavior()
{
}

SymbolBehavior::SymbolOptions SymbolBehavior::options() const
{
    return m_options;
}

void SymbolBehavior::setOptions(const SymbolOptions &options)
{
    m_options = options;
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
    setData(LP::SymbolType, type);
}
