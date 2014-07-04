/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "commonapplication.h"

CommonApplication::CommonApplication()
{
}

QList<SymbolBehavior> CommonApplication::paletteSymbols() const
{
    return m_paletteSymbols;
}

void CommonApplication::setPaletteSymbols(const QList<SymbolBehavior> &symbols)
{
    m_paletteSymbols = symbols;
}
