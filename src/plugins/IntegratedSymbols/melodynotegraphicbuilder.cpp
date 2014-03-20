/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "melodynotegraphicbuilder.h"
#include <common/datatypes/pitch.h>
#include <common/datatypes/length.h>
#include <common/itemdataroles.h>
#include <QPainter>
#include <QPixmap>

namespace {

qreal SpaceBetweenNoteheadAndDots = 0;
qreal SpaceBetweenDots = 0;

}

MelodyNoteGraphicBuilder::MelodyNoteGraphicBuilder()
{
    initSpaceBetweenNoteheadAndDots();
    initSpaceBetweenDots();
}

QPixmap MelodyNoteGraphicBuilder::pixmapForActualItemData()
{
    QRectF pixmapRect = rectForActualItemData();

    QPixmap pixmap(pixmapRect.width(), pixmapRect.height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    painter.translate(0.0, yOffsetForNotehead(pixmapRect.height()));
    addNotehead(&painter);

    painter.resetTransform();
    painter.translate(xOffsetForDots(), yOffsetForDots(pixmapRect.height()));
    addDots(&painter);

    return pixmap;
}

QRectF MelodyNoteGraphicBuilder::rectForActualItemData()
{
    QRectF rect = musicFont()->boundingRectForGlyph(MusicFont::Noteheads_s1);

    int dotCount = data(LP::MelodyNoteDots).value<int>();
    qreal dotWidth = musicFont()->boundingRectForGlyph(MusicFont::Dot).width();
    qreal dotsTotalWidth = dotCount * dotWidth + (dotCount - 1) * SpaceBetweenDots;

    rect.adjust(0, 0, SpaceBetweenNoteheadAndDots + dotsTotalWidth, 0);

    return rect;
}

qreal MelodyNoteGraphicBuilder::yOffsetForNotehead(qreal pixmapHeight)
{
    qreal noteheadHeight = musicFont()->boundingRectForGlyph(actualNoteheadGlyph()).height();
    qreal offset = pixmapHeight - noteheadHeight + noteheadHeight /2;
    return offset;
}

qreal MelodyNoteGraphicBuilder::xOffsetForDots()
{
    qreal noteHeadWidth = musicFont()->boundingRectForGlyph(actualNoteheadGlyph()).width();
    return noteHeadWidth + SpaceBetweenNoteheadAndDots;
}

qreal MelodyNoteGraphicBuilder::yOffsetForDots(qreal pixmapHeight)
{
    qreal dotHeight = musicFont()->boundingRectForGlyph(MusicFont::Dot).height();
    if (isPitchOnLine()) {
        return dotHeight / 2;
    } else {
        return yOffsetForNotehead(pixmapHeight);
    }
}

void MelodyNoteGraphicBuilder::addNotehead(QPainter *painter)
{
    musicFont()->paintGlyph(painter, actualNoteheadGlyph());
}

MusicFont::Glyph MelodyNoteGraphicBuilder::actualNoteheadGlyph()
{
    Length::Value length = data(LP::SymbolLength).value<Length::Value>();
    if (length < Length::_4)
        return MusicFont::Noteheads_s1;
    return MusicFont::Noteheads_s2;
}

void MelodyNoteGraphicBuilder::addDots(QPainter *painter)
{
    qreal dotWidth = musicFont()->boundingRectForGlyph(MusicFont::Dot).width();
    painter->save();
    QVariant dotCountVariant = data(LP::MelodyNoteDots);
    if (dotCountVariant.isValid() &&
            dotCountVariant.canConvert<int>()) {

        int dotCount = dotCountVariant.value<int>();

        for (int i = 0; i < dotCount; i++) {
            musicFont()->paintGlyph(painter, MusicFont::Dot);
            painter->translate(SpaceBetweenDots + dotWidth, 0.0);
        }
    }

    painter->restore();
}

void MelodyNoteGraphicBuilder::initSymbolGraphic()
{
    QPixmap pixmap = pixmapForActualItemData();
    setSymbolGraphicPixmap(pixmap);
}

void MelodyNoteGraphicBuilder::updateSymbolGraphic(const QVariant &value, int key)
{
    Q_UNUSED(value);
    Q_UNUSED(key);
    initSymbolGraphic();
}

QVector<int> MelodyNoteGraphicBuilder::graphicDataRoles() const
{
    QVector<int> dataRoles;
    dataRoles.append(LP::SymbolPitch);
    dataRoles.append(LP::SymbolLength);
    dataRoles.append(LP::MelodyNoteDots);

    return dataRoles;
}

bool MelodyNoteGraphicBuilder::isPitchOnLine()
{
    QVariant pitchVar = data(LP::SymbolPitch);
    if (pitchVar.isValid() && pitchVar.canConvert<PitchPtr>()) {
        PitchPtr pitch = pitchVar.value<PitchPtr>();
        if (pitch->staffPos() % 2) {
            return false;
        }
        return true;
    }
    return false;
}

void MelodyNoteGraphicBuilder::initSpaceBetweenNoteheadAndDots()
{
    if (SpaceBetweenNoteheadAndDots != 0)
        return;

    QRectF dot = musicFont()->boundingRectForGlyph(MusicFont::Dot);
    SpaceBetweenNoteheadAndDots = 0.8 * dot.width();
}

void MelodyNoteGraphicBuilder::initSpaceBetweenDots()
{
    if (SpaceBetweenDots != 0)
        return;

    QRectF dot = musicFont()->boundingRectForGlyph(MusicFont::Dot);
    SpaceBetweenDots = 0.7 * dot.width();
}
