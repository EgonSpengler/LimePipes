/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include <QFontMetricsF>
#include "SMuFL/smufl.h"
#include "glyphitem.h"

GlyphItem::GlyphItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
}

GlyphItem::GlyphItem(const QString &glyphName, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setGlyphName(glyphName);
}

void GlyphItem::initFromGlyphName(const QString &glyphName)
{
    if (m_smufl.isNull() || glyphName.isEmpty())
        return;

    quint32 codepoint = m_smufl->codepointForGlyph(glyphName);
    m_char = QChar(codepoint);

    QFontMetricsF metrics(m_smufl->font());
    QRectF newBoundingRect(metrics.boundingRect(m_char));
    if (m_boundingRect != newBoundingRect) {
        m_boundingRect = newBoundingRect;
        QGraphicsItem::prepareGeometryChange();
    } else {
        update();
    }
}

SMuFLPtr GlyphItem::smufl() const
{
    return m_smufl;
}

void GlyphItem::setSmufl(const SMuFLPtr &smufl)
{
    if (m_smufl == smufl)
        return;

    m_smufl = smufl;
    initFromGlyphName(m_glyphName);
    smuflHasChanged(m_smufl);
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
    return m_boundingRect;
}

void GlyphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_smufl.isNull() || m_char.isNull())
        return;

    painter->setFont(m_smufl->font());
    painter->drawText(0, 0, m_char);

    // Bounding rect
//    QPen pen(Qt::blue);
//    pen.setWidthF(1.0);
//    painter->setPen(pen);
//    painter->drawRect(m_boundingRect);
}
