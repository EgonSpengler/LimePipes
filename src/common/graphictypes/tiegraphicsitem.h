/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIEGRAPHICSITEM_H
#define TIEGRAPHICSITEM_H

#include <QList>
#include <QGraphicsPathItem>

#include <common/graphictypes/MusicFont/musicfont.h>

class GlyphItem;

class TieGraphicsItem : public QGraphicsPathItem
{
public:
    explicit TieGraphicsItem(QGraphicsItem *parent = 0);

    void addGlyph(GlyphItem *item);
    void removeGlyph(GlyphItem *item);

    MusicFontPtr musicFont() const;
    void setMusicFont(const MusicFontPtr &musicFont);

private:
    void checkIfHasGlyphAndUpdate(GlyphItem *item);
    void updatePath();
    void reposition();
    QList<GlyphItem*> m_spanningGlyphs;
    MusicFontPtr m_musicFont;
};

#endif // TIEGRAPHICSITEM_H
