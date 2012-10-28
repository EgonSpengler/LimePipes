/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "symbolgraphicbuilder.h"

MusicFontPtr SymbolGraphicBuilder::s_musicFont = MusicFontPtr(0);

SymbolGraphicBuilder::SymbolGraphicBuilder(MusicItem *item)
    : m_item(item)
{
    initSymbolGraphic();

    // resources aren't available in static initialization,
    // so initialize in first call of constructor
    if (s_musicFont.data() == 0) {
        s_musicFont = MusicFontPtr(new EmmentalerMusicFont(20));
    }
}

void SymbolGraphicBuilder::setLineHeight(int lineHeight)
{
    s_musicFont->setLineHeight(lineHeight);
}

qreal SymbolGraphicBuilder::lineHeight() const
{
    return s_musicFont->lineHeight();
}

void SymbolGraphicBuilder::initSymbolGraphic()
{
    m_graphic = SymbolGraphicPtr(new SymbolGraphic());
}
