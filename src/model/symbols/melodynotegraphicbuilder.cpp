/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "melodynotegraphicbuilder.h"
#include <model/datatypes/pitch.h>
#include <model/datatypes/length.h>
#include <model/itemdatatypes.h>
#include <QPainter>
#include <QPixmapCache>

#include <QDebug>

namespace {

qreal spaceBetweenGlyphs = 0;

const QString NoteHeadWithHole("noteHeadWithHole");
const QString NoteHeadWithoutHole("noteHeadWithoutHole");
const QString Dot("Dot");

}

MelodyNoteGraphicBuilder::MelodyNoteGraphicBuilder(MusicItem *item)
    : SymbolGraphicBuilder(item)
{
    if (spaceBetweenGlyphs == 0) {
        initSpaceBetweenGlyphs();
    }

    createPixmaps(200);
}

void MelodyNoteGraphicBuilder::createPixmaps(int lineHeight)
{
    Q_UNUSED(lineHeight)

    createNoteheads();
    createDot();
}

void MelodyNoteGraphicBuilder::updateSymbolGraphic()
{
    if (!itemHasRequiredData())
        return;

    QPixmap pixmap = pixmapForActualItemData();
    setSymbolGraphicPixmap(pixmap);
}

QPixmap MelodyNoteGraphicBuilder::pixmapForActualItemData()
{
    //QRectF pixmapRect = rectForActualItemData();

    QPixmap pixmap;
    Length::Value length = itemData(LP::symbolLength).value<Length::Value>();
    if (length < Length::_4) {
        if (!QPixmapCache::find(NoteHeadWithHole, pixmap)) {
            createNoteheads();
            QPixmapCache::find(NoteHeadWithHole, pixmap);
        }
    } else {
        if (!QPixmapCache::find(NoteHeadWithoutHole, pixmap)) {
            createNoteheads();
            QPixmapCache::find(NoteHeadWithoutHole, pixmap);
        }
    }

    return pixmap;
}

QRectF MelodyNoteGraphicBuilder::rectForActualItemData()
{
    return QRectF();
}

void MelodyNoteGraphicBuilder::createNoteheads()
{
    QRectF noteheadRect = musicFont()->boundingRectForGlyph(MusicFont::Noteheads_s1);
    QPixmap noteheadPixmap(noteheadRect.size().toSize());
    noteheadPixmap.fill(Qt::transparent);

    QPainter painter(&noteheadPixmap);
    painter.translate(0.0, noteheadRect.height() / 2);

    musicFont()->paintGlyph(&painter, MusicFont::Noteheads_s1);
    QPixmapCache::insert(NoteHeadWithHole, noteheadPixmap);

    noteheadPixmap.fill(Qt::transparent);

    musicFont()->paintGlyph(&painter, MusicFont::Noteheads_s2);
    QPixmapCache::insert(NoteHeadWithoutHole, noteheadPixmap);
}

void MelodyNoteGraphicBuilder::createDot()
{
    QRectF dotRect = musicFont()->boundingRectForGlyph(MusicFont::Dot);
    QPixmap dotPixmap(dotRect.size().toSize());
    dotPixmap.fill(Qt::transparent);

    QPainter painter(&dotPixmap);
    painter.translate(0.0, dotRect.height() / 2);

    musicFont()->paintGlyph(&painter, MusicFont::Dot);
    QPixmapCache::insert(Dot, dotPixmap);
}

bool MelodyNoteGraphicBuilder::isSymbolGraphicAffectedByDataRole(int role)
{
    if (role == LP::symbolPitch ||
        role == LP::symbolLength)
        return true;
    return false;
}

bool MelodyNoteGraphicBuilder::isPitchOnLine()
{
    QVariant pitchVar = itemData(LP::symbolPitch);
    if (pitchVar.isValid() && pitchVar.canConvert<PitchPtr>()) {
        PitchPtr pitch = pitchVar.value<PitchPtr>();
        if (pitch->staffPos() % 2) {
            return false;
        }
        return true;
    }
    return false;
}

bool MelodyNoteGraphicBuilder::itemHasRequiredData()
{
    if (itemData(LP::symbolPitch).isValid() &&
        itemData(LP::symbolLength).isValid()) {
        return true;
    }
    return false;
}

void MelodyNoteGraphicBuilder::initSpaceBetweenGlyphs()
{
    QRectF dot = musicFont()->boundingRectForGlyph(MusicFont::Dot);
    spaceBetweenGlyphs = 1.3 * dot.width();
}
