/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include "tst_emmentalermusicfonttest.h"

#include <QDebug>

void EmmentalerMusicFontTest::initTestCase()
{
    m_musicFont = new EmmentalerMusicFont(m_lineHeight);
}

void EmmentalerMusicFontTest::cleanupTestCase()
{
    delete m_musicFont;
}

void EmmentalerMusicFontTest::testLineHeightOfNoteHead()
{
    QRectF boundingRect = m_musicFont->boundingRectForGlyph(MusicFont::Noteheads_s1);
    qDebug() << "Bounding rect: " << boundingRect;
    qDebug() << "line height: " << m_lineHeight;
    bool heightInRange = (boundingRect.height() == m_lineHeight ||
                          boundingRect.height() == m_lineHeight + 1);
    QVERIFY2(heightInRange, "Notehead hasn't got line height or line height+1");
}

void EmmentalerMusicFontTest::testNumberGlyphs_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("Zero") <<    MusicFont::Zero <<  0x0030;
    QTest::newRow("One") <<     MusicFont::One <<   0x0031;
    QTest::newRow("Two") <<     MusicFont::Two <<   0x0032;
    QTest::newRow("Three") <<   MusicFont::Three << 0x0033;
    QTest::newRow("Four") <<    MusicFont::Four <<  0x0034;
    QTest::newRow("Five") <<    MusicFont::Five <<  0x0035;
    QTest::newRow("Six") <<     MusicFont::Six <<   0x0036;
    QTest::newRow("Seven") <<   MusicFont::Seven << 0x0037;
    QTest::newRow("Eight") <<   MusicFont::Eight << 0x0038;
    QTest::newRow("Nine") <<    MusicFont::Nine <<  0x0039;
}

void EmmentalerMusicFontTest::testNumberGlyphs()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

void EmmentalerMusicFontTest::testCharGlyphs_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("F") <<    MusicFont::F <<  0x0066;
    QTest::newRow("M") <<    MusicFont::M <<  0x006D;
    QTest::newRow("P") <<    MusicFont::P <<  0x0070;
    QTest::newRow("R") <<    MusicFont::R <<  0x0072;
    QTest::newRow("S") <<    MusicFont::S <<  0x0073;
    QTest::newRow("Z") <<    MusicFont::Z <<  0x007A;
}

void EmmentalerMusicFontTest::testCharGlyphs()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

void EmmentalerMusicFontTest::testRestGlyphs_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("0") <<    MusicFont::Rests_0 <<      0xE100;
    QTest::newRow("1") <<    MusicFont::Rests_1 <<      0xE101;
    QTest::newRow("0o") <<   MusicFont::Rests_0o <<     0xE102;
    QTest::newRow("1o") <<   MusicFont::Rests_1o <<     0xE103;
    QTest::newRow("M3") <<   MusicFont::Rests_M3 <<     0xE104;
    QTest::newRow("M2") <<   MusicFont::Rests_M2 <<     0xE105;
    QTest::newRow("M1") <<   MusicFont::Rests_M1 <<     0xE106;
    QTest::newRow("2") <<    MusicFont:: Rests_2<<      0xE107;
    QTest::newRow("2classical") <<    MusicFont::Rests_2classical <<  0xE108;
    QTest::newRow("3") <<    MusicFont::Rests_3 <<      0xE109;
    QTest::newRow("4") <<    MusicFont::Rests_4 <<      0xE10A;
    QTest::newRow("5") <<    MusicFont::Rests_5 <<      0xE10B;
    QTest::newRow("6") <<    MusicFont::Rests_6 <<      0xE10C;
    QTest::newRow("7") <<    MusicFont::Rests_7 <<      0xE10D;
}

void EmmentalerMusicFontTest::testRestGlyphs()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

void EmmentalerMusicFontTest::testAccidentalGlyphs_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("sharp") <<           MusicFont::Accidentals_Sharp <<                         0xE10E;
    QTest::newRow("sharparrowup") <<    MusicFont::Accidentals_Sharp_ArrowUp <<                 0xE10F;
    QTest::newRow("sharparrowdown") <<  MusicFont::Accidentals_Sharp_ArrowDown <<               0xE110;
    QTest::newRow("sharparrowboth") <<  MusicFont::Accidentals_Sharp_ArrowBoth <<               0xE111;
    QTest::newRow("2Sl1St") <<          MusicFont::Accidentals_Sharp_SlashSlash_Stem <<         0xE112;
    QTest::newRow("3Sl2St") <<          MusicFont::Accidentals_Sharp_SlashSlashSlash_StemStem <<0xE113;
    QTest::newRow("3Sl1St") <<          MusicFont::Accidentals_Sharp_SlashSlashSlash_Stem <<    0xE114;
    QTest::newRow("2Sl3St") <<          MusicFont::Accidentals_Sharp_SlashSlash_StemStemStem << 0xE115;
}

void EmmentalerMusicFontTest::testAccidentalGlyphs()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

void EmmentalerMusicFontTest::testClefs_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("C") <<   MusicFont::Clefs_C <<   0xE16C;
    QTest::newRow("F") <<   MusicFont::Clefs_F <<   0xE16E;
    QTest::newRow("G") <<   MusicFont::Clefs_G <<   0xE170;
    QTest::newRow("Perc") <<MusicFont::Clefs_Percussion << 0xE172;
    QTest::newRow("Tab") << MusicFont::Clefs_Tab << 0xE174;
}

void EmmentalerMusicFontTest::testClefs()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

void EmmentalerMusicFontTest::testTimeSigs_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("C44") << MusicFont::TimeSig_C44 << 0xE176;
    QTest::newRow("C22") << MusicFont::TimeSig_C22 << 0xE177;
}

void EmmentalerMusicFontTest::testTimeSigs()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

void EmmentalerMusicFontTest::testNoteheads_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("S0") << MusicFont::Noteheads_s0 << 0xE18D;
    QTest::newRow("S1") << MusicFont::Noteheads_s1 << 0xE18E;
    QTest::newRow("S2") << MusicFont::Noteheads_s2 << 0xE18F;
}

void EmmentalerMusicFontTest::testNoteheads()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

void EmmentalerMusicFontTest::testDots_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("Dot") << MusicFont::Dot << 0xE130;
}

void EmmentalerMusicFontTest::testDots()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

void EmmentalerMusicFontTest::testFlags_data()
{
    QTest::addColumn<MusicFont::Glyph>("Glyph");
    QTest::addColumn<int>("Glyphnumber");

    QTest::newRow("u3") << MusicFont::Flags_u3 << 0xE218;
    QTest::newRow("u4") << MusicFont::Flags_u4 << 0xE219;
    QTest::newRow("u5") << MusicFont::Flags_u5 << 0xE21A;
    QTest::newRow("u6") << MusicFont::Flags_u6 << 0xE21B;
    QTest::newRow("u7") << MusicFont::Flags_u7 << 0xE21C;
    QTest::newRow("d3") << MusicFont::Flags_d3 << 0xE21D;
    QTest::newRow("d4") << MusicFont::Flags_d4 << 0xE21E;
    QTest::newRow("d5") << MusicFont::Flags_d5 << 0xE21F;
    QTest::newRow("d6") << MusicFont::Flags_d6 << 0xE220;
    QTest::newRow("d7") << MusicFont::Flags_d7 << 0xE221;
}

void EmmentalerMusicFontTest::testFlags()
{
    QFETCH(MusicFont::Glyph, Glyph);
    QFETCH(int, Glyphnumber);

    QCOMPARE(m_musicFont->glyphNumber(Glyph), Glyphnumber);
}

QTEST_MAIN(EmmentalerMusicFontTest)

#include "tst_emmentalermusicfonttest.moc"
