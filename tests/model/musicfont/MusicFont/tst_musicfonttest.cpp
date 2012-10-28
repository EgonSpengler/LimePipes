/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <musicfont.h>

#include <QDebug>

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
