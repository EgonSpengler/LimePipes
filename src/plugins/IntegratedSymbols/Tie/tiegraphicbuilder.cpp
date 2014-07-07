/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>

#include <common/itemdataroles.h>
#include <common/defines.h>
#include "tiegraphicbuilder.h"

TieGraphicBuilder::TieGraphicBuilder()
{
    m_dataRoles << LP::SymbolSpanType;
    m_dataRoles << LP::SymbolSpanBuddy;
}

QVector<int> TieGraphicBuilder::graphicDataRoles() const
{
    return m_dataRoles;
}

void TieGraphicBuilder::updateSymbolGraphic(const QVariant &value, int key)
{
    if (key == LP::SymbolSpanType) {
        m_spanType = value.value<SpanType>();
    }

    if (key == LP::SymbolSpanBuddy) {
        m_buddyIndex = value.toModelIndex();
    }

}
