/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "smufl.h"

SMuFL::SMuFL()
{
}

SMuFL::~SMuFL()
{
}

QFont SMuFL::font() const
{
    return QFont();
}

Engravings SMuFL::engravings() const
{
    return Engravings{0};
}

GlyphData SMuFL::glyphData(const QString &glyphname)
{
    GlyphData data;
    data.nominalWidth = 0;
    return data;
}

qreal SMuFL::staffSpace() const
{
    return font().pixelSize() / 4;
}

qreal SMuFL::halfStaffSpace() const
{
    return font().pixelSize() / 8;
}

quint32 SMuFL::codepointForGlyph(const QString &glyphname) const
{
    return 0;
}

quint32 SMuFL::alternateCodepointForGlyph(const QString &glyphname) const
{
    return 0;
}
