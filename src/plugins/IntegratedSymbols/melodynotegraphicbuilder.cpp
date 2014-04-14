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
#include <common/graphictypes/glyphitem.h>
#include <QPainter>
#include <QPixmap>

namespace {

qreal SpaceBetweenNoteheadAndDots = 0;
qreal SpaceBetweenDots = 0;

}

MelodyNoteGraphicBuilder::MelodyNoteGraphicBuilder()
    : m_glyph(0)
{
    m_glyph = new GlyphItem("noteheadBlack");
    initSpaceBetweenNoteheadAndDots();
    initSpaceBetweenDots();
}

void MelodyNoteGraphicBuilder::smuflChanged(const SMuFLPtr &smufl)
{
    m_glyph->setSmufl(smufl);
}

QPixmap MelodyNoteGraphicBuilder::pixmapForActualItemData()
{
//    QRectF pixmapRect = rectForActualItemData();

//    QPixmap pixmap(pixmapRect.width(), pixmapRect.height());
//    pixmap.fill(Qt::transparent);
//    QPainter painter(&pixmap);

//    painter.translate(0.0, yOffsetForNotehead(pixmapRect.height()));
//    addNotehead(&painter);

//    painter.resetTransform();
//    painter.translate(xOffsetForDots(), yOffsetForDots(pixmapRect.height()));
//    addDots(&painter);

//    return pixmap;
    return QPixmap();
}

void MelodyNoteGraphicBuilder::updateSymbolGraphic(const QVariant &value, int key)
{
    Q_UNUSED(value);
    Q_UNUSED(key);
    QPixmap pixmap = pixmapForActualItemData();
    setSymbolGraphicPixmap(pixmap);
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

//    QRectF dot = musicFont()->boundingRectForGlyph(MusicFont::Dot);
//    SpaceBetweenNoteheadAndDots = 0.8 * dot.width();
}

void MelodyNoteGraphicBuilder::initSpaceBetweenDots()
{
    if (SpaceBetweenDots != 0)
        return;

//    QRectF dot = musicFont()->boundingRectForGlyph(MusicFont::Dot);
//    SpaceBetweenDots = 0.7 * dot.width();
}


GlyphItem *MelodyNoteGraphicBuilder::glyphItem() const
{
    return m_glyph;
}
