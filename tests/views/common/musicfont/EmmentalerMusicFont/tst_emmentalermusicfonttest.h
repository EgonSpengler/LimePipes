/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef EMMENTALERMUSICFONTTEST_H
#define EMMENTALERMUSICFONTTEST_H

#include <QObject>
#include <QMetaType>
#include <src/views/common/musicfont/emmentalermusicfont.h>

Q_DECLARE_METATYPE(MusicFont::Glyph)

class EmmentalerMusicFontTest : public QObject
{
    Q_OBJECT

public:
    EmmentalerMusicFontTest()
        : m_lineHeight(100),
          m_musicFont(0) {}

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testLineHeightOfNoteHead();
    void testNumberGlyphs_data();
    void testNumberGlyphs();
    void testCharGlyphs_data();
    void testCharGlyphs();
    void testRestGlyphs_data();
    void testRestGlyphs();
    void testAccidentalGlyphs_data();
    void testAccidentalGlyphs();
    void testClefs_data();
    void testClefs();
    void testTimeSigs_data();
    void testTimeSigs();
    void testNoteheads_data();
    void testNoteheads();
    void testDots_data();
    void testDots();
    void testFlags_data();
    void testFlags();

private:
    int m_lineHeight;
    EmmentalerMusicFont *m_musicFont;
};

#endif
