/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include "melodynoteglyphitem.h"

static const QString WholeNoteHead("noteheadWhole");
static const QString HalfNoteHead("noteheadHalf");
static const QString BlackNoteHead("noteheadBlack");

MelodyNoteGlyphItem::MelodyNoteGlyphItem()
    : GlyphItem()
{
    m_notehead = new GlyphItem(this);
}

void MelodyNoteGlyphItem::setLength(Length::Value length)
{
    m_notehead->setGlyphName(noteheadForLength(length));
}

QString MelodyNoteGlyphItem::noteheadForLength(Length::Value length)
{
    switch (length) {
    case Length::_1:
        return WholeNoteHead; break;
    case Length::_2:
        return HalfNoteHead; break;
    default:
        return BlackNoteHead; break;
    }
}

void MelodyNoteGlyphItem::smuflHasChanged(const SMuFLPtr &smufl)
{
    m_notehead->setSmufl(smufl);
}
