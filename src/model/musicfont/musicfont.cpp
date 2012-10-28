/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicfont.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFontMetricsF>
#include <QRectF>
#include <QPainter>

namespace {

qreal initialPointSize = 20;

}

MusicFont::MusicFont(int lineHeight)
    : m_lineHeight(lineHeight), m_font(QFont())
{
    m_font.setPointSizeF(initialPointSize);
}

void MusicFont::addGlyphNumber(MusicFont::Glyph glyph, int number)
{
    m_glyphNumbers.insert(glyph, number);
}

void MusicFont::setFont(const QFont &font)
{
    m_font = font;
    updateFont();
}

void MusicFont::updateFont()
{
    if (QCoreApplication::instance() == NULL) {
        qWarning() << "No QCoreApplication. Code will segfault...";
    }

    m_font.setPointSizeF(initialPointSize);
    Glyph lineHeightGlyph = Noteheads_s1;

    // Line height glyph must be supported by font
    int lineHeightGlyphNumber = glyphNumber(lineHeightGlyph);
    if (lineHeightGlyphNumber == 0) {
        qWarning() << "Glyph Notehead_s1 isn't supported by font. It is needed for calculating point size";
        return;
    }

    // Calculate new font's point size for line height
    // If boundingRect won't scale to line height,
    // accept a size of line height + 1
    QRectF lineHeightGlyphRect;
    do {
        setNewPointSizeToHeightOfGlyph(lineHeightGlyph);
        lineHeightGlyphRect = boundingRectForGlyph(lineHeightGlyph);

    } while (lineHeightGlyphRect.height() != m_lineHeight &&
             lineHeightGlyphRect.height() != m_lineHeight + 1);
}

void MusicFont::setNewPointSizeToHeightOfGlyph(Glyph lineHeightGlyph)
{
    QRectF lineHeightGlyphBoundingRect = boundingRectForGlyph(lineHeightGlyph);
    qreal newPointSize = (qreal)m_lineHeight / lineHeightGlyphBoundingRect.height() * m_font.pointSizeF();

    m_font.setPointSizeF(newPointSize);
}

int MusicFont::glyphNumber(MusicFont::Glyph glyph)
{
    return m_glyphNumbers.value(glyph, 0);
}

QRectF MusicFont::boundingRectForGlyph(MusicFont::Glyph glyph)
{
    int glyphFontNumber = glyphNumber(glyph);
    if (glyphFontNumber == 0)
        return QRectF();

    QChar fontChar = QChar(glyphFontNumber);
    QFontMetricsF fm = QFontMetricsF(m_font);
    return fm.boundingRect(fontChar);
}

void MusicFont::paintGlyph(QPainter *painter, MusicFont::Glyph glyph)
{
    painter->save();

    painter->setFont(m_font);
    painter->drawText(0, 0, QString(QChar(glyphNumber(glyph))));

    painter->restore();
}

void MusicFont::setLineHeight(int lineHeight)
{
    if (m_lineHeight != lineHeight) {
        m_lineHeight = lineHeight;
        updateFont();
    }
}

qreal MusicFont::lineHeight() const
{
    return m_lineHeight;
}
