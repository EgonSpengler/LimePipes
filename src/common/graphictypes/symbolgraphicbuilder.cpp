/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 * @class SymbolGraphicBuilder symbolgraphicbuilder.h
 * @brief SymbolGraphicBuilder are used by graphic symbols to create the graphics. symbolGraphic() returnes the Graphic, which is used as
 *         data with the LP::symbolGraphic role. Subclasses have to reimplement updateSymbolGraphic and update the graphic
 *         by using the protected functions.
 *
 * @fn void SymbolGraphicBuilder::updateSymbolGraphic(const QVariant& data, in key)
 * @brief This method can be implemented by subclasses to update their appearance according to data.
 *        This method will be called, when data for a role has changed which is returned by
 *        SymbolGraphicBuilder::graphicDataRoles().
 *
 * @fn void SymbolGraphicBuilder::graphicDataRoles()
 * @brief Subclasses can return a QVector of the dataroles, which affect a change of the graphic.
 *
 */

#include "symbolgraphicbuilder.h"
#include "musicfont/emmentalermusicfont.h"

MusicFontPtr SymbolGraphicBuilder::s_musicFont = MusicFontPtr(0);

namespace {
const int InitialLineHeight = 8;
}

SymbolGraphicBuilder::SymbolGraphicBuilder()
{
    initSymbolGraphicMember();

    // resources aren't available in static initialization,
    // so initialize in first call of constructor
    if (s_musicFont.data() == 0) {
        s_musicFont = MusicFontPtr(new EmmentalerMusicFont(InitialLineHeight));
    }
}

void SymbolGraphicBuilder::setStaffLineHeight(int lineHeight)
{
    s_musicFont->setStaffLineHeight(lineHeight);
}

int SymbolGraphicBuilder::staffLineHeight() const
{
    return s_musicFont->staffLineHeight();
}

void SymbolGraphicBuilder::setData(const QVariant &value, int key)
{
    if (!graphicDataRoles().contains(key))
        return;

    if (m_graphicData.value(key) != value &&
            value.isValid()) {
        m_graphicData.insert(key, value);
        updateSymbolGraphic(value, key);
    }
}

QVariant SymbolGraphicBuilder::data(int key) const
{
    return m_graphicData.value(key);
}

void SymbolGraphicBuilder::setSymbolGraphicPixmap(const QPixmap &pixmap)
{
    m_graphic->setPixmap(pixmap);
}

void SymbolGraphicBuilder::setSymbolGraphicYOffset(qreal yOffset)
{
    m_graphic->setYOffset(yOffset);
}

void SymbolGraphicBuilder::initSymbolGraphicMember()
{
    m_graphic = SymbolGraphicPtr(new SymbolGraphic());
}
