/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicfont.h"
#include <QPalette>

MusicFont::MusicFont()
{
}

MusicFont::~MusicFont()
{
}

QFont MusicFont::font() const
{
    return QFont();
}

Engravings MusicFont::engravings() const
{
    return Engravings{0};
}

GlyphData MusicFont::glyphData(const QString &glyphname)
{
    GlyphData data;
    data.nominalWidth = 0;
    return data;
}

QColor MusicFont::fontColor(const FontColor &color) const
{
    return QColor();
}

qreal MusicFont::staffSpace() const
{
    return font().pixelSize() / 4;
}

qreal MusicFont::halfStaffSpace() const
{
    return font().pixelSize() / 8;
}

quint32 MusicFont::codepointForGlyph(const QString &glyphname) const
{
    return 0;
}

quint32 MusicFont::alternateCodepointForGlyph(const QString &glyphname) const
{
    return 0;
}
