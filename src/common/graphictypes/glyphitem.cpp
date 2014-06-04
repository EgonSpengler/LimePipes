/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include <QFontMetricsF>
#include <QDebug>
#include "MusicFont/musicfont.h"
#include "glyphitem.h"

GlyphItem::GlyphItem(QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_colorRole(FontColor::Normal)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

GlyphItem::GlyphItem(const QString &glyphName, QGraphicsItem *parent)
    : QGraphicsItem(parent),
      m_colorRole(FontColor::Normal)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setGlyphName(glyphName);
}

void GlyphItem::initFromGlyphName(const QString &glyphName)
{
    if (m_musicFont.isNull() || glyphName.isEmpty())
        return;

    quint32 codepoint = m_musicFont->codepointForGlyph(glyphName);
    m_char = QChar(codepoint);

    QFontMetricsF metrics(m_musicFont->font());
    QRectF newBoundingRect(metrics.boundingRect(m_char));
    if (m_boundingRect != newBoundingRect) {
        m_boundingRect = newBoundingRect;
        QGraphicsItem::prepareGeometryChange();
    } else {
        update();
    }
}

MusicFontPtr GlyphItem::musicFont() const
{
    return m_musicFont;
}

void GlyphItem::setMusicFont(const MusicFontPtr &musicFont)
{
    if (m_musicFont == musicFont)
        return;

    m_musicFont = musicFont;
    initFromGlyphName(m_glyphName);
    musicFontHasChanged(m_musicFont);
}

void GlyphItem::setColorRole(const FontColor &colorRole)
{
    if (m_colorRole == colorRole)
        return;

    m_colorRole = colorRole;
    colorRoleHasChanged(m_colorRole);
    update();
}

FontColor GlyphItem::colorRole() const
{
    return m_colorRole;
}

QVariant GlyphItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange) {
        bool selected = value.toBool();
        FontColor color = FontColor::Normal;
        if (selected) {
            color = FontColor::Selected;
        }
        setColorRole(color);
        qDebug() << "Glyph item has selected state: " << selected;
    }

    return QGraphicsItem::itemChange(change, value);
}

QString GlyphItem::glyphName() const
{
    return m_glyphName;
}

void GlyphItem::setGlyphName(const QString &glyphName)
{
    if (m_glyphName == glyphName ||
            glyphName.isEmpty())
        return;

    m_glyphName = glyphName;
    initFromGlyphName(m_glyphName);
}

QRectF GlyphItem::boundingRect() const
{
    if (m_glyphName.isEmpty()) {
        return childrenBoundingRect();
    }

    return m_boundingRect;
}

void GlyphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_musicFont.isNull() || m_char.isNull())
        return;

    QColor color(m_musicFont->fontColor(m_colorRole));
    painter->setPen(color);
    painter->setFont(m_musicFont->font());
    painter->drawText(0, 0, m_char);

    // Bounding rect
    QPen pen(Qt::blue);
    pen.setWidthF(1.0);
    painter->setPen(pen);
    painter->drawRect(m_boundingRect);
}
