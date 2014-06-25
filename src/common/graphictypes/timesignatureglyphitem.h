/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIMESIGNATUREGLYPHITEM_H
#define TIMESIGNATUREGLYPHITEM_H

#include <common/datatypes/timesignature.h>

#include "glyphitem.h"

class TimeSignatureGlyphItem : public GlyphItem
{
public:
    explicit TimeSignatureGlyphItem(QGraphicsItem *parent = 0);

    TimeSignature::Type signatureType() const;
    void setSignatureType(const TimeSignature::Type &signatureType);

private:
    QString timeSigGlyphNameForNumber(int number);
    void layoutGlyphs();
    GlyphItem *m_beatCountGlyph;
    GlyphItem *m_beatUnitGlyph;
    TimeSignature::Type m_signatureType;
};

#endif // TIMESIGNATUREGLYPHITEM_H
