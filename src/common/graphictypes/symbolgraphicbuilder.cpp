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

#include <common/itemdataroles.h>
#include "glyphitem.h"
#include "symbolgraphicbuilder.h"

SymbolGraphicBuilder::SymbolGraphicBuilder()
    : m_symbolType(0)
{
}

GlyphItem *SymbolGraphicBuilder::glyphItem() const
{
    return 0;
}

void SymbolGraphicBuilder::setData(const QVariant &value, int key)
{
    if (key == LP::SymbolType) {
        setSymbolType(value.toInt());
    }

    if (!graphicDataRoles().contains(key))
        return;

    if (m_graphicData.value(key) != value &&
            value.isValid()) {
        m_graphicData.insert(key, value);
        updateSymbolGraphic(value, key);
        emit dataChanged(value, key);
    }
}

QVariant SymbolGraphicBuilder::data(int key) const
{
    return m_graphicData.value(key);
}
int SymbolGraphicBuilder::symbolType() const
{
    return m_symbolType;
}

void SymbolGraphicBuilder::setSymbolType(int symbolType)
{
    m_symbolType = symbolType;
}

