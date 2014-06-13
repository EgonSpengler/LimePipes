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

class GlyphItem;

class TieGraphicsItem : public QGraphicsPathItem
{
public:
    explicit TieGraphicsItem(QGraphicsItem *parent = 0);

    void addGlyph(GlyphItem *item);
    void removeGlyph(GlyphItem *item);

private:
    void updatePath();
    void reposition();
    QList<GlyphItem*> m_spanningGlyphs;
};

#endif // TIEGRAPHICSITEM_H
