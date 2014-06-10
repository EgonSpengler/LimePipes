/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>
#include "tiegraphicbuilder.h"

TieGraphicBuilder::TieGraphicBuilder()
{
    m_dataRoles << LP::SymbolSpanType;
}

QVector<int> TieGraphicBuilder::graphicDataRoles() const
{
    return m_dataRoles;
}

void TieGraphicBuilder::updateSymbolGraphic(const QVariant &value, int key)
{
}

void TieGraphicBuilder::musicFontChanged(const MusicFontPtr &musicFont)
{
}
