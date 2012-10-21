/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "symbolgraphicbuilder.h"

SymbolGraphicBuilder::SymbolGraphicBuilder(MusicItem *item)
    : m_item(item)
{
    initSymbolGraphic();
}

void SymbolGraphicBuilder::initSymbolGraphic()
{
    m_graphic = SymbolGraphicPtr(new SymbolGraphic());
}
