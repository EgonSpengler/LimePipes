/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICFONT_H
#define MUSICFONT_H

#include <QFont>
#include <QHash>
#include <QSharedPointer>

class QRectF;
class QPainter;

class MusicFont
{
public:
    enum Glyph {
        // Numbers
        Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,

        // Chars
        F, M, P, R, S, Z,

        // Rests
        Rests_0, Rests_1, Rests_0o, Rests_1o, Rests_M3, Rests_M2, Rests_M1,
        Rests_2, Rests_2classical, Rests_3, Rests_4, Rests_5, Rests_6, Rests_7,

        // Accidentals
        Accidentals_Sharp, Accidentals_Sharp_ArrowUp, Accidentals_Sharp_ArrowDown, Accidentals_Sharp_ArrowBoth,
        Accidentals_Sharp_SlashSlash_Stem, Accidentals_Sharp_SlashSlashSlash_StemStem, Accidentals_Sharp_SlashSlashSlash_Stem,
        Accidentals_Sharp_SlashSlash_StemStemStem,

        // Clefs
        Clefs_C, Clefs_F, Clefs_G, Clefs_Percussion, Clefs_Tab,

        // TimeSigs
        TimeSig_C44, TimeSig_C22,

        // Noteheads
        Noteheads_s0, Noteheads_s1, Noteheads_s2,

        // Dots
        Dot,

        // Flags
        Flags_u3, Flags_u4, Flags_u5, Flags_u6, Flags_u7, Flags_d3, Flags_d4, Flags_d5, Flags_d6, Flags_d7
    };

    explicit MusicFont(int lineHeight);
    virtual ~MusicFont() { }

    void paintGlyph(QPainter *painter, Glyph glyph);

    void setLineHeight(int lineHeight);
    int lineHeight() const;

    int glyphNumber(Glyph glyph);
    QRectF boundingRectForGlyph(Glyph glyph);

protected:
    void addGlyphNumber(Glyph glyph, int number);
    void setFont(const QFont &font);

private:
    void updateFont();
    void setNewPointSizeToHeightOfGlyph(Glyph lineHeightGlyph);
    int m_lineHeight;
    QFont m_font;
    QHash<Glyph, int> m_glyphNumbers;
};

typedef QSharedPointer<MusicFont> MusicFontPtr;

#endif // MUSICFONT_H
