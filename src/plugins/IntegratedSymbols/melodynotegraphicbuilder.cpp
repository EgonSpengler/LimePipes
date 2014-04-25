/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "melodynotegraphicbuilder.h"
#include <common/datatypes/length.h>
#include <common/itemdataroles.h>
#include <common/graphictypes/glyphitem.h>
#include <MelodyNote/melodynoteglyphitem.h>
#include <QPainter>
#include <QPixmap>

namespace {

qreal SpaceBetweenNoteheadAndDots = 0;
qreal SpaceBetweenDots = 0;

}

MelodyNoteGraphicBuilder::MelodyNoteGraphicBuilder()
    : m_glyph(0)
{
    m_glyph = new MelodyNoteGlyphItem();
}

void MelodyNoteGraphicBuilder::updateSymbolGraphic(const QVariant &value, int key)
{
    if (key == LP::SymbolLength) {
        Length::Value length = value.value<Length::Value>();
        m_glyph->setLength(length);
    }
    if (key == LP::SymbolPitch) {
        PitchPtr pitch = value.value<PitchPtr>();
        m_glyph->setNoteIsOnLine(isPitchOnLine(pitch));
    }
    if (key == LP::MelodyNoteDots) {
        int dots = value.toInt();
        m_glyph->setDots(dots);
    }
}

bool MelodyNoteGraphicBuilder::isPitchOnLine(const PitchPtr &pitch) const
{
    if (pitch->staffPos() % 2) {
        return false;
    }
    return true;
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

QVector<int> MelodyNoteGraphicBuilder::graphicDataRoles() const
{
    QVector<int> dataRoles;
    dataRoles.append(LP::SymbolPitch);
    dataRoles.append(LP::SymbolLength);
    dataRoles.append(LP::MelodyNoteDots);

    return dataRoles;
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
