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
#include <common/datatypes/pitch.h>
#include <common/graphictypes/glyphitem.h>

#include "symbolgraphicbuilder.h"
#include "stemglyphitem.h"
#include "stemengraver.h"

StemEngraver::StemEngraver()
{
}

void StemEngraver::insertGraphicsBuilder(int index, SymbolGraphicBuilder *builder)
{
    if (builder->glyphItem() == 0) {
        qWarning() << "StemEngraver: Can't insert graphcis builder with no glyph item";
        return;
    }

    StemData data;
    data.graphicBuilder = builder;
    data.glyphItem = new StemGlyphItem;
    if (builder->glyphItem()) {
        data.glyphItem->connectColorRoleToGlyph(builder->glyphItem());
    }

    data.glyphItem->setStemDirection(StemGlyphItem::Downwards);

    m_stemDatas.insert(index, data);
    GlyphItem *builderItem = builder->glyphItem();
    if (builderItem) {
        data.glyphItem->setMusicFont(musicFont());
        data.glyphItem->setParentItem(builderItem);
    }
    QObject::connect(builder, &SymbolGraphicBuilder::dataChanged,
                     [this, builder] (const QVariant& data, int role) {
        builderDataChanged(builder, data, role);
    });

    // Init
    builderDataChanged(builder, builder->data(LP::SymbolLength), LP::SymbolLength);
    builderDataChanged(builder, builder->data(LP::SymbolPitch), LP::SymbolPitch);
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
    if (role == LP::SymbolPitch) {
        PitchPtr pitch = data.value<PitchPtr>();
        StemData stemData = stemDataWithGraphicBuilder(builder);
        if (!stemData.glyphItem)
            return;
        stemData.glyphItem->setPitch(pitch);
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
