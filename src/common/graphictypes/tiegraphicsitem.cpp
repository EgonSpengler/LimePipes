/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "tiegraphicsitem.h"

TieGraphicsItem::TieGraphicsItem(QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
{
}

void TieGraphicsItem::addGlyph(GlyphItem *item)
{
    if (!m_spanningGlyphs.contains(item)) {
        m_spanningGlyphs.append(item);
        updatePath();
        reposition();
    }
}

void TieGraphicsItem::removeGlyph(GlyphItem *item)
{
    if (!m_spanningGlyphs.contains(item))
        return;

    m_spanningGlyphs.removeAll(item);
    updatePath();
    reposition();
}

void TieGraphicsItem::updatePath()
{

}

void TieGraphicsItem::reposition()
{

}
