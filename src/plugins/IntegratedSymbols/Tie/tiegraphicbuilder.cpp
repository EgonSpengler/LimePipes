/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>

#include <common/itemdataroles.h>
#include <common/graphicsmapperinterface.h>
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
        m_spanType = value.value<SymbolSpanType>();
    }

    if (key == LP::SymbolSpanBuddy) {
        m_buddyIndex = value.toModelIndex();
        if (graphicsMapper()) {
            QGraphicsItem *buddyItem = graphicsMapper()->itemForIndex(m_buddyIndex);
            if (m_spanType == SymbolSpanType::Start)
                qDebug() << "Start Span item";
            else
                qDebug() << "End Span item";

            if (!buddyItem) {
                qDebug() << "No buddy graphics item returned for index";
            } else {
                GraphicsItemType buddyType = static_cast<GraphicsItemType>(buddyItem->type());
                qDebug() << "Buddy is a " << buddyType;
            }
        }
    }

}

void TieGraphicBuilder::musicFontChanged(const MusicFontPtr &musicFont)
{
}
