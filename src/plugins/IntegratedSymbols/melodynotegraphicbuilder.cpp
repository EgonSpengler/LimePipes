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
        setLedgerLinesForPitch(pitch);
    }
    if (key == LP::MelodyNoteDots) {
        int dots = value.toInt();
        m_glyph->setDots(dots);
    }
    if (key == LP::SymbolPitchContext) {
        m_pitchContext = value.value<PitchContextPtr>();
    }
}

bool MelodyNoteGraphicBuilder::isPitchOnLine(const PitchPtr &pitch) const
{
    if (pitch->staffPos() % 2) {
        return false;
    }
    return true;
}

void MelodyNoteGraphicBuilder::setLedgerLinesForPitch(const PitchPtr &pitch)
{
    if (m_pitchContext.isNull())
        return;

    int staffPos = pitch->staffPos();
    int ledgerLineCount = ledgerLineCountForStaffPos(staffPos);
    m_glyph->setLedgerLines(ledgerLineCount, staffPos < 0);
}

int MelodyNoteGraphicBuilder::ledgerLineCountForStaffPos(int staffPos)
{
    if (m_pitchContext.isNull())
        return 0;

    StaffType staffType = m_pitchContext->staffType();
    if (staffType == StaffType::Standard) {
        if (staffPos >= -1 &&
                staffPos <= 9) {
            return 0;
        }

        // Above
        if (staffPos < 0) {
            return static_cast<int>(staffPos / 2 * -1);
        } else {
        // Below staff
            return static_cast<int>((staffPos - 8) / 2);
        }
    }

    return 0;
}

void MelodyNoteGraphicBuilder::smuflChanged(const SMuFLPtr &smufl)
{
    m_glyph->setSmufl(smufl);
}

QVector<int> MelodyNoteGraphicBuilder::graphicDataRoles() const
{
    QVector<int> dataRoles;
    dataRoles.append(LP::SymbolPitch);
    dataRoles.append(LP::SymbolLength);
    dataRoles.append(LP::MelodyNoteDots);
    dataRoles.append(LP::SymbolPitchContext);

    return dataRoles;
}

GlyphItem *MelodyNoteGraphicBuilder::glyphItem() const
{
    return m_glyph;
}
