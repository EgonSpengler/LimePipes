/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "clefglyphitem.h"

ClefGlyphItem::ClefGlyphItem(ClefType type, QGraphicsItem *parent)
    : GlyphItem(glyphNameForClef(type), parent)
{
    m_clefType = type;
    setScenePosChangeEnabled(true);
}

QString ClefGlyphItem::glyphNameForClef(ClefType type)
{
    switch (type) {
    case ClefType::Soprano:
    case ClefType::MezzoSoprano:
    case ClefType::Alto:
    case ClefType::Tenor:
    case ClefType::BaritoneC:
        return QStringLiteral("cClef");
    case ClefType::Treble:
    case ClefType::FrenchViolin:
        return QStringLiteral("gClef");
    case ClefType::Bass:
    case ClefType::BaritoneF:
    case ClefType::Subbass:
        return QStringLiteral("fClef");
    default:
        return QStringLiteral("gClef");
    }
}

ClefType ClefGlyphItem::clef() const
{
    return m_clefType;
}

void ClefGlyphItem::setClef(const ClefType &clefType)
{
    m_clefType = clefType;
    setGlyphName(glyphNameForClef(clefType));
}

qreal ClefGlyphItem::yOffset() const
{
    qreal offset = 0;
    qreal staffSpace = musicFont()->staffSpace();

    switch (m_clefType) {
    case ClefType::Treble:
    case ClefType::MezzoSoprano:
        offset = 3 * staffSpace;
        break;
    case ClefType::FrenchViolin:
    case ClefType::Soprano:
        offset = 4 * staffSpace;
        break;
    case ClefType::Alto:
    case ClefType::BaritoneF:
        offset = 2 * staffSpace;
        break;
    case ClefType::Bass:
    case ClefType::Tenor:
        offset = 1 * staffSpace;
        break;
    case ClefType::BaritoneC:
    case ClefType::Subbass:
        break;
    }

    return offset;
}
