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
}

QString ClefGlyphItem::glyphNameForClef(ClefType type)
{
    switch (type) {
    case ClefType::C:
        return QStringLiteral("cClef");
    case ClefType::G:
        return QStringLiteral("gClef");
    case ClefType::F:
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

