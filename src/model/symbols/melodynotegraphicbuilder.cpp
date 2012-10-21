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

MelodyNoteGraphicBuilder::MelodyNoteGraphicBuilder(MusicItem *item)
    : SymbolGraphicBuilder(item)
{
}

void MelodyNoteGraphicBuilder::createPixmaps(qreal lineHeight)
{
    Q_UNUSED(lineHeight)
}

void MelodyNoteGraphicBuilder::updateSymbolGraphic()
{
    if (!itemHasRequiredData())
        return;

    Length::Value length = itemData(LP::symbolLength).value<Length::Value>();

    if (length < Length::_4) {
        setSymbolGraphicPixmap(QPixmap(":/symbols/melody_note_2"));
    } else {
        setSymbolGraphicPixmap(QPixmap(":/symbols/melody_note_4"));
    }
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
