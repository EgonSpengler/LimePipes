/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QObject>
#include <QDebug>

#include <common/itemdataroles.h>
#include <common/datatypes/length.h>

#include "symbolgraphicbuilder.h"
#include "stemglyphitem.h"
#include "stemengraver.h"

StemEngraver::StemEngraver()
{
}

void StemEngraver::insertGraphicsBuilder(int index, SymbolGraphicBuilder *builder)
{
    StemData data;
    data.graphicBuilder = builder;
    data.glyphItem = new StemGlyphItem;

    m_stemDatas.insert(index, data);
    QObject::connect(builder, &SymbolGraphicBuilder::dataChanged,
                     [this, builder] (const QVariant& data, int role) {
        builderDataChanged(builder, data, role);
    });
}

void StemEngraver::removeGraphicsBuilder(SymbolGraphicBuilder *builder)
{
    StemData dataToRemove = stemDataWithGraphicBuilder(builder);
    StemGlyphItem *stemGlyph = dataToRemove.glyphItem;
    if (!stemGlyph)
        return;

    delete dataToRemove.glyphItem;
    dataToRemove.glyphItem = 0;
}

void StemEngraver::builderDataChanged(SymbolGraphicBuilder *builder, const QVariant &data, int role)
{
    if (!data.isValid())
        return;

    if (role == LP::SymbolLength) {
        Length::Value length = data.value<Length::Value>();
        StemData stemData = stemDataWithGraphicBuilder(builder);
        if (!stemData.glyphItem)
            return;
        stemData.glyphItem->setLength(length);
    }
}

StemData StemEngraver::stemDataWithGraphicBuilder(SymbolGraphicBuilder *builder)
{
    foreach (StemData data, m_stemDatas) {
        if (data.graphicBuilder == builder) {
            return data;
        }
    }

    return StemData();
}

MusicFontPtr StemEngraver::musicFont() const
{
    return m_musicFont;
}

void StemEngraver::setMusicFont(const MusicFontPtr &musicFont)
{
    m_musicFont = musicFont;
}

