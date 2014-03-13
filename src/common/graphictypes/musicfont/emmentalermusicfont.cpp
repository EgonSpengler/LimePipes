/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "emmentalermusicfont.h"
#include <QFontDatabase>
#include <QDebug>

EmmentalerMusicFont::EmmentalerMusicFont(int lineHeight)
    : MusicFont(lineHeight)
{
    addNumberGlyphs();
    addCharGlyphs();
    addRestGlyphs();
    addAccidentalGlyphs();
    addClefGlyphs();
    addTimeSigGlyphs();
    addNoteheadGlyphs();
    addDotGlyphs();
    addFlagGlyphs();

    int fontLoaded = QFontDatabase::addApplicationFont(":/musicfonts/emmentaler-11");
    if (fontLoaded == -1) {
        qWarning() << "Emmentaler font can't be loaded";
        return;
    }

    QFont font("Emmentaler-11");
    setFont(font);
}

void EmmentalerMusicFont::addNumberGlyphs()
{
    addGlyphNumber(Zero,    0x0030);
    addGlyphNumber(One,     0x0031);
    addGlyphNumber(Two,     0x0032);
    addGlyphNumber(Three,   0x0033);
    addGlyphNumber(Four,    0x0034);
    addGlyphNumber(Five,    0x0035);
    addGlyphNumber(Six,     0x0036);
    addGlyphNumber(Seven,   0x0037);
    addGlyphNumber(Eight,   0x0038);
    addGlyphNumber(Nine,    0x0039);
}

void EmmentalerMusicFont::addCharGlyphs()
{
    addGlyphNumber(F, 0x0066);
    addGlyphNumber(M, 0x006D);
    addGlyphNumber(P, 0x0070);
    addGlyphNumber(R, 0x0072);
    addGlyphNumber(S, 0x0073);
    addGlyphNumber(Z, 0x007A);
}

void EmmentalerMusicFont::addRestGlyphs()
{
    addGlyphNumber(Rests_0,     0xE100);
    addGlyphNumber(Rests_1,     0xE101);
    addGlyphNumber(Rests_0o,    0xE102);
    addGlyphNumber(Rests_1o,    0xE103);
    addGlyphNumber(Rests_M3,    0xE104);
    addGlyphNumber(Rests_M2,    0xE105);
    addGlyphNumber(Rests_M1,    0xE106);
    addGlyphNumber(Rests_2,     0xE107);
    addGlyphNumber(Rests_2classical,
                   0xE108);
    addGlyphNumber(Rests_3,     0xE109);
    addGlyphNumber(Rests_4,     0xE10A);
    addGlyphNumber(Rests_5,     0xE10B);
    addGlyphNumber(Rests_6,     0xE10C);
    addGlyphNumber(Rests_7,     0xE10D);
}

void EmmentalerMusicFont::addAccidentalGlyphs()
{
    addGlyphNumber(Accidentals_Sharp,                           0xE10E);
    addGlyphNumber(Accidentals_Sharp_ArrowUp,                   0xE10F);
    addGlyphNumber(Accidentals_Sharp_ArrowDown,                 0xE110);
    addGlyphNumber(Accidentals_Sharp_ArrowBoth,                 0xE111);
    addGlyphNumber(Accidentals_Sharp_SlashSlash_Stem,           0xE112);
    addGlyphNumber(Accidentals_Sharp_SlashSlashSlash_StemStem,  0xE113);
    addGlyphNumber(Accidentals_Sharp_SlashSlashSlash_Stem,      0xE114);
    addGlyphNumber(Accidentals_Sharp_SlashSlash_StemStemStem,   0xE115);
}

void EmmentalerMusicFont::addClefGlyphs()
{
    addGlyphNumber(Clefs_C,     0xE16C);
    addGlyphNumber(Clefs_F,     0xE16E);
    addGlyphNumber(Clefs_G,     0xE170);
    addGlyphNumber(Clefs_Percussion,
                   0xE172);
    addGlyphNumber(Clefs_Tab,   0xE174);
}

void EmmentalerMusicFont::addTimeSigGlyphs()
{
    addGlyphNumber(TimeSig_C44, 0xE176);
    addGlyphNumber(TimeSig_C22, 0xE177);
}

void EmmentalerMusicFont::addNoteheadGlyphs()
{
    addGlyphNumber(Noteheads_s0, 0xE18D);
    addGlyphNumber(Noteheads_s1, 0xE18E);
    addGlyphNumber(Noteheads_s2, 0xE18F);
}

void EmmentalerMusicFont::addDotGlyphs()
{
    addGlyphNumber(Dot, 0xE130);
}

void EmmentalerMusicFont::addFlagGlyphs()
{
    addGlyphNumber(Flags_u3, 0xE218);
    addGlyphNumber(Flags_u4, 0xE219);
    addGlyphNumber(Flags_u5, 0xE21A);
    addGlyphNumber(Flags_u6, 0xE21B);
    addGlyphNumber(Flags_u7, 0xE21C);
    addGlyphNumber(Flags_d3, 0xE21D);
    addGlyphNumber(Flags_d4, 0xE21E);
    addGlyphNumber(Flags_d5, 0xE21F);
    addGlyphNumber(Flags_d6, 0xE220);
    addGlyphNumber(Flags_d7, 0xE221);
}
