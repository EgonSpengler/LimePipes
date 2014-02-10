/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICFONTTEST_H
#define MUSICFONTTEST_H

#include <QObject>
#include <src/views/common/musicfont/musicfont.h>

namespace {

class TestMusicFont : public MusicFont
{
public:
    TestMusicFont(int lineHeight)
        : MusicFont(lineHeight),
          m_testGlyphNumber(0x0042),
          m_lineHeightGlyphNumber(0x0061),
          m_testGlyph(MusicFont::Accidentals_Sharp),
          m_lineHeightGlyph(MusicFont::Noteheads_s1)  // Noteheads_s1 is used for calculating line height
    {
        addGlyphNumber(m_testGlyph, m_testGlyphNumber);
        addGlyphNumber(m_lineHeightGlyph, m_lineHeightGlyphNumber);
        m_font = QFont("Arial");
        setFont(m_font);
    }
    QFont testFont() { return m_font; }
    MusicFont::Glyph testGlyph() { return m_testGlyph; }
    int testGlyphNumber() { return m_testGlyphNumber; }
    MusicFont::Glyph lineHeightGlyph() { return m_lineHeightGlyph; }
    int lineHeightGlyphNumber() { return m_lineHeightGlyphNumber; }

private:
    QFont m_font;
    int m_testGlyphNumber;
    int m_lineHeightGlyphNumber;
    MusicFont::Glyph m_testGlyph;
    MusicFont::Glyph m_lineHeightGlyph;
};

}

class MusicFontTest : public QObject
{
    Q_OBJECT

public:
    MusicFontTest();

private Q_SLOTS:
    void testGlyphNumber();
    void testBoundingRectForGlyph();
};

#endif

