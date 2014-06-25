/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "timesignatureglyphitem.h"

TimeSignatureGlyphItem::TimeSignatureGlyphItem(QGraphicsItem *parent)
    : GlyphItem(parent)
{
    m_beatCountGlyph = new GlyphItem(this);
    connect(m_beatCountGlyph, &GlyphItem::widthHasChanged,
            this, &GlyphItem::widthHasChanged);
    m_beatUnitGlyph  = new GlyphItem(this);
    connect(m_beatUnitGlyph, &GlyphItem::widthHasChanged,
            this, &GlyphItem::widthHasChanged);
    layoutGlyphs();
}

TimeSignature::Type TimeSignatureGlyphItem::signatureType() const
{
    return m_signatureType;
}

void TimeSignatureGlyphItem::setSignatureType(const TimeSignature::Type &signatureType)
{
    m_signatureType = signatureType;
    int beatCount = TimeSignature::beatCount(m_signatureType);
    m_beatCountGlyph->setGlyphName(timeSigGlyphNameForNumber(beatCount));
    int beatUnit = TimeSignature::beatUnit(m_signatureType);
    m_beatUnitGlyph->setGlyphName(timeSigGlyphNameForNumber(beatUnit));
}

QString TimeSignatureGlyphItem::timeSigGlyphNameForNumber(int number)
{
    if (number < 0 ||
            number > 9)
        number = 0;

    QString nameTemplate("timeSig%1");
    return nameTemplate.arg(number);
}

void TimeSignatureGlyphItem::layoutGlyphs()
{
    qreal staffSpace = musicFont()->staffSpace();
    m_beatCountGlyph->setY(1 * staffSpace);
    m_beatUnitGlyph->setY(3 * staffSpace);
}


