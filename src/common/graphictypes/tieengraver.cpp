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

SpanType TieEngraver::spanTypeOfBuilder(SymbolGraphicBuilder *builder)
{
    SpanType spanType = builder->data(LP::SymbolSpanType).value<SpanType>();

    return spanType;
}

SymbolGraphicBuilder *TieEngraver::startItemBuilderBefore(int index)
{
    if (!m_graphicBuilder.count())
        return 0;

    SymbolGraphicBuilder *startItemBuilder;
    for (int i = index; i >= 0; --i) {
        startItemBuilder = m_graphicBuilder.at(i);
        if (spanTypeOfBuilder(startItemBuilder) == SpanType::Start ||
                spanTypeOfBuilder(startItemBuilder) == SpanType::End) {
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
        if (spanTypeOfBuilder(endItemBuilder) == SpanType::Start ||
                spanTypeOfBuilder(endItemBuilder) == SpanType::End) {
            break;
        }
    }
    return endItemBuilder;
}

void TieEngraver::insertGraphicsBuilder(int index, SymbolGraphicBuilder *builder)
{
    if (builder->symbolType() == LP::Tie) {
        SpanType spanType = spanTypeOfBuilder(builder);
        if (spanType == SpanType::Start) {
            // TieGraphicsItem will have no parent item per default.
            // It will add itself to the graphics scene, when items are added
            TieGraphicsItem *tieItem = new TieGraphicsItem;
            tieItem->setMusicFont(musicFont());
            m_tieItems.insert(builder, tieItem);

            SymbolGraphicBuilder *endItemBuilder = endItemBuilderAfter(index);
            if (!endItemBuilder)
                return;

            if (spanTypeOfBuilder(endItemBuilder) == SpanType::End) {
                m_tieItems.insert(endItemBuilder, tieItem);
            }
        } else {
            SymbolGraphicBuilder *startItemBuilder = startItemBuilderBefore(index);
            if (!startItemBuilder)
                return;

            if (spanTypeOfBuilder(startItemBuilder) == SpanType::Start) {
                TieGraphicsItem *tieItem = m_tieItems.value(startItemBuilder);
                if (!tieItem) {
                    qWarning() << "TieEngraver: Tie Start graphics builder has no tie item";
                    return;
                }
                m_tieItems.insert(builder, tieItem);
            }
        }
        QString spanTypeName = QStringLiteral("start");
        if (spanType == SpanType::End)
            spanTypeName = "end";

        qDebug() << "TieEngraver: Inserted Tie " << spanTypeName << " symbol at "
                    << index;
    }

    m_graphicBuilder.insert(index, builder);

    if (builder->symbolType() == LP::Tie) {
        return;
    }

    if (builder->glyphItem()) {
        SymbolGraphicBuilder *tieStart = 0;

        // Search for tie start directly before newly inserted symbol
        for (int i = index; i >= 0; --i) {
            tieStart = m_graphicBuilder.at(i);
            SpanType spanType = spanTypeOfBuilder(tieStart);

            if (spanType == SpanType::Start) {
                break;
            }
            if (spanType == SpanType::End ||
                    i == 0) {
                tieStart = 0;
                break;
            }
        }

        if (!tieStart) {
            return;
        }

        TieGraphicsItem *tieItem = m_tieItems.value(tieStart);
        if (!tieItem)
            return;

        tieItem->addGlyph(builder->glyphItem());
    }
}

void TieEngraver::removeGraphicsBuilder(SymbolGraphicBuilder *builder)
{
    m_graphicBuilder.removeAll(builder);
    m_tieItems.remove(builder);
}

void TieEngraver::musicFontHasChanged(const MusicFontPtr &musicFont)
{
    foreach (TieGraphicsItem *tieGraphic, m_tieItems) {
        tieGraphic->setMusicFont(musicFont);
    }
}
