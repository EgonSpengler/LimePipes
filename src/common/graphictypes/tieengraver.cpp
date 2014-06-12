/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/defines.h>
#include <common/itemdataroles.h>
#include <common/graphictypes/symbolgraphicbuilder.h>

#include "tiegraphicsitem.h"
#include "tieengraver.h"

TieEngraver::TieEngraver()
{
}

SymbolSpanType TieEngraver::spanTypeOfBuilder(SymbolGraphicBuilder *builder)
{
    SymbolSpanType spanType = builder->data(LP::SymbolSpanType).value<SymbolSpanType>();

    return spanType;
}

SymbolGraphicBuilder *TieEngraver::startItemBuilderBefore(int index)
{
    if (!m_graphicBuilder.count())
        return 0;

    SymbolGraphicBuilder *startItemBuilder;
    for (int i = index; i >= 0; --i) {
        startItemBuilder = m_graphicBuilder.at(i);
        if (spanTypeOfBuilder(startItemBuilder) == SymbolSpanType::Start ||
                spanTypeOfBuilder(startItemBuilder) == SymbolSpanType::End) {
            break;
        }
    }
    return startItemBuilder;
}

SymbolGraphicBuilder *TieEngraver::endItemBuilderAfter(int index)
{
    if (!m_graphicBuilder.count())
        return 0;

    SymbolGraphicBuilder *endItemBuilder;
    for (int i = 0; i <= index; ++i) {
        endItemBuilder = m_graphicBuilder.at(i);
        if (spanTypeOfBuilder(endItemBuilder) == SymbolSpanType::Start ||
                spanTypeOfBuilder(endItemBuilder) == SymbolSpanType::End) {
            break;
        }
    }
    return endItemBuilder;
}

void TieEngraver::insertGraphicsBuilder(int index, SymbolGraphicBuilder *builder)
{
    m_graphicBuilder.insert(index, builder);

    if (builder->symbolType() == LP::Tie) {
        SymbolSpanType spanType = spanTypeOfBuilder(builder);
        if (spanType == SymbolSpanType::Start) {
            TieGraphicsItem *tieItem = new TieGraphicsItem;
            m_tieItems.insert(builder, tieItem);

            SymbolGraphicBuilder *endItemBuilder = endItemBuilderAfter(index);
            if (!endItemBuilder)
                return;

            if (spanTypeOfBuilder(endItemBuilder) == SymbolSpanType::End) {
                m_tieItems.insert(endItemBuilder, tieItem);
            }
        } else {
            SymbolGraphicBuilder *startItemBuilder = startItemBuilderBefore(index);
            if (!startItemBuilder)
                return;

            if (spanTypeOfBuilder(startItemBuilder) == SymbolSpanType::Start) {
                TieGraphicsItem *tieItem = m_tieItems.value(startItemBuilder);
                if (!tieItem) {
                    qWarning() << "TieEngraver: Tie Start graphics builder has no tie item";
                    return;
                }
                m_tieItems.insert(builder, tieItem);
            }
        }
        QString spanTypeName = QStringLiteral("start");
        if (spanType == SymbolSpanType::End)
            spanTypeName = "end";

        qDebug() << "TieEngraver: Inserted Tie " << spanTypeName << " symbol at "
                    << index;
    }

}

void TieEngraver::removeGraphicsBuilder(SymbolGraphicBuilder *builder)
{
    m_graphicBuilder.removeAll(builder);
    m_tieItems.remove(builder);
}
