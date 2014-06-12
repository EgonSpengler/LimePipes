/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "tiegraphicsitem.h"

TieGraphicsItem::TieGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

void TieGraphicsItem::addGlyph(GlyphItem *item)
{
    if (!m_spanningGlyphs.contains(item)) {
        m_spanningGlyphs.append(item);
    }
}

void TieGraphicsItem::removeGlyph(GlyphItem *item)
{
    m_spanningGlyphs.removeAll(item);
}


QRectF TieGraphicsItem::boundingRect() const
{
    return QRectF();
}

void TieGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}
