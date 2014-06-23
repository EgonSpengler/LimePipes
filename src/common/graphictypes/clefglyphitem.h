/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef CLEFGLYPHITEM_H
#define CLEFGLYPHITEM_H

#include <common/defines.h>

#include "glyphitem.h"

class ClefGlyphItem : public GlyphItem
{
public:
    ClefGlyphItem(ClefType type = ClefType::Treble, QGraphicsItem *parent = 0);

    ClefType clef() const;
    void setClef(const ClefType &clef);

    qreal yOffset() const;
private:
    QString glyphNameForClef(ClefType type);
    ClefType m_clefType;
};

#endif // CLEFGLYPHITEM_H
