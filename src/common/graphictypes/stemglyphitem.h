/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef STEMGLYPHITEM_H
#define STEMGLYPHITEM_H

#include <QGraphicsLineItem>
#include <common/datatypes/length.h>
#include <common/datatypes/pitch.h>
#include "glyphitem.h"

class QGraphicsLineItem;

class StemGlyphItem : public GlyphItem
{
public:
    enum Direction {
        Upwards,
        Downwards
    };

    explicit StemGlyphItem();

    void setLength(Length::Value length);

    void setPitch(const Pitch &pitch);

    void setStemLengthFactor(qreal staffSpaceFactor);

    Direction stemDirection() const;
    void setStemDirection(const Direction &stemDirection);

    void setFlagGlyph(Length::Value length);

    // GlyphItem interface
protected:
    void musicFontHasChanged(const MusicFontPtr &musicFont);
    void colorRoleHasChanged(const FontColor &colorRole);

private:
    QString flagGlyphNameFromLength(Length::Value length);
    void layoutFlagGlyphAndStem();
    GlyphItem *m_flagItem;
    QGraphicsLineItem *m_stemItem;
    Direction m_stemDirection;
    qreal m_stemLengthFactor;
};

#endif // STEMGLYPHITEM_H
