/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class SymbolGraphicBuilder symbolgraphicbuilder.h
  * @brief SymbolGraphicBuilder are used by graphic symbols to create the graphics. symbolGraphic() returnes the Graphic, which is used as
  *         data with the LP::symbolGraphic role. Subclasses have to reimplement updateSymbolGraphic and update the graphic
  *         by using the protected functions.
  *
  * @fn void SymbolGraphicBuilder::createPixmaps(int lineHeight)
  * @brief This method will be called for an initialization. E.g. cache often used or verry common pixmaps.
  *
  * @fn void SymbolGraphicBuilder::updateSymbolGraphic()
  * @brief Update the data of the SymbolGraphic. If data is written and isSymbolGraphicAffectedByDataRole returns true,
  *         This method will be called.
  *
  * @fn bool SymbolGraphicBuilder::isSymbolGraphicAffectedByDataRole(int role)
  * @brief Subclasses should return true, if the graphic needs an update if this data role changes.
  *
  */

#include "symbolgraphicbuilder.h"
#include <model/musicfont/emmentalermusicfont.h>

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
