/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QObject>
#include <QGraphicsScene>

#include "glyphitem.h"
#include "tiegraphicsitem.h"

TieGraphicsItem::TieGraphicsItem(QGraphicsItem *parent)
    : QGraphicsPathItem(parent)
{
}

void TieGraphicsItem::addGlyph(GlyphItem *item)
{
    if (!m_spanningGlyphs.contains(item)) {
        m_spanningGlyphs.append(item);
        QObject::connect(item, &GlyphItem::xChanged,
                         [this, item] {
            checkIfHasGlyphAndUpdate(item);
        });
        QObject::connect(item, &GlyphItem::yChanged,
                [this, item] {
            checkIfHasGlyphAndUpdate(item);
        });
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
    if (!m_spanningGlyphs.count()) {
        if (scene()) {
            scene()->removeItem(this);
        }
        return;
    }

    QRectF glyphItemsSceneRect;
    foreach (const GlyphItem *glyph, m_spanningGlyphs) {
        QRectF glyphBoundingRect(glyph->boundingRect());
        QRectF sceneItemRect(glyph->mapToScene(glyphBoundingRect).boundingRect());
        glyphItemsSceneRect = glyphItemsSceneRect.united(sceneItemRect);
    }

    qreal width = glyphItemsSceneRect.width();
    qreal height = glyphItemsSceneRect.width() / 3;
    qreal midThickness = height / 2;

    QPointF startPoint(0, 0);
    QPointF endPoint(width, 0);
    QPainterPath path(startPoint);

    QPointF midPoint1(width / 2, -height);
    path.quadTo(midPoint1, endPoint);

    QPointF midPoint2(width / 2, -height + midThickness);
    path.quadTo(midPoint2, startPoint);

    setPath(path);

    if (!scene()) {
        m_spanningGlyphs.at(0)->scene()->addItem(this);
        setVisible(true);
    }

    setPos(glyphItemsSceneRect.topLeft());
}

void TieGraphicsItem::reposition()
{

}

MusicFontPtr TieGraphicsItem::musicFont() const
{
    return m_musicFont;
}

void TieGraphicsItem::setMusicFont(const MusicFontPtr &musicFont)
{
    m_musicFont = musicFont;
}

void TieGraphicsItem::checkIfHasGlyphAndUpdate(GlyphItem *item)
{
    if (!m_spanningGlyphs.contains(item))
        return;

    updatePath();
}

