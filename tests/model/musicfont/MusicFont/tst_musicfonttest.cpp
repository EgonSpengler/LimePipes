/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "tst_musicfonttest.h"

MusicFontTest::MusicFontTest()
{
}

void MusicFontTest::testGlyphNumber()
{
    TestMusicFont musicFont(30);
    QVERIFY2(musicFont.glyphNumber(MusicFont::Accidentals_Sharp) == musicFont.testGlyphNumber(), "Can't get back correct glyph number");
    QVERIFY2(musicFont.glyphNumber(MusicFont::TimeSig_C22) == 0, "Default glyph number isn't correct");
}

void MusicFontTest::testBoundingRectForGlyph()
{
    int lineHeight = 53;
    TestMusicFont musicFont(lineHeight);

    QRectF glyphRect = musicFont.boundingRectForGlyph(musicFont.lineHeightGlyph());

    QVERIFY2(glyphRect.height() == lineHeight, "Line height glyph must have a heigt of line height");
}

QTEST_MAIN(MusicFontTest)

#include "tst_musicfonttest.moc"
