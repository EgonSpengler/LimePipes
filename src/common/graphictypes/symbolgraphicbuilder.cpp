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
#include "musicfont/emmentalermusicfont.h"

MusicFontPtr SymbolGraphicBuilder::s_musicFont = MusicFontPtr(0);

namespace {
const int InitialLineHeight = 8;
}

SymbolGraphicBuilder::SymbolGraphicBuilder()
    : m_graphicWasInitialized(false)
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
        bool initializeStateBefore = m_graphicWasInitialized;
        handleInitOfSymbolGraphic(value, key);
        m_graphicData.insert(key, value);

        // Call update only if initializeSymbolGraphic was called before
        // and not in this call of setData
        if (m_graphicWasInitialized &&
                m_graphicWasInitialized == initializeStateBefore) {
            updateSymbolGraphic(value, key);
        }
    }
}

void SymbolGraphicBuilder::handleInitOfSymbolGraphic(const QVariant &value, int key)
{
    if (m_graphicWasInitialized)
        return;

    int currentDataCount = m_graphicData.count();
    int neededDataCount  = graphicDataRoles().count();
    if (currentDataCount + 1 != neededDataCount)
        return;

    if (graphicDataRoles().contains(key) &&
            !m_graphicData.contains(key)) {
        initializeSymbolGraphic();
        m_graphicWasInitialized = true;
    }
}

QVariant SymbolGraphicBuilder::data(int key) const
{
    return m_graphicData.value(key);
}

bool SymbolGraphicBuilder::isGraphicValid() const
{
    foreach (int requiredRole, graphicDataRoles()) {
        if (!m_graphicData.value(requiredRole).isValid()) {
            return false;
        }
    }

    return true;
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
