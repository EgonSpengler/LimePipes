/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include "SMuFL/smufl.h"
#include "glyphitem.h"

GlyphItem::GlyphItem(const QString &glyphName, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    setGlyphName(glyphName);
}

void GlyphItem::initFromGlyphName(const QString &glyphName)
{
    if (m_smufl.isNull())
        return;

    quint32 codepoint = m_smufl->codepointForGlyph(glyphName);
    m_char = QChar(codepoint);
}

SMuFLPtr GlyphItem::smufl() const
{
    return m_smufl;
}

void GlyphItem::setSmufl(const SMuFLPtr &smufl)
{
    m_smufl = smufl;
    initFromGlyphName(m_glyphName);
}

QString GlyphItem::glyphName() const
{
    return m_glyphName;
}

void GlyphItem::setGlyphName(const QString &glyphName)
{
    m_glyphName = glyphName;
}


QRectF GlyphItem::boundingRect() const
{
    return QRectF(0, 0, 20, 20);
}

void GlyphItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_smufl.isNull())
        return;

    painter->setFont(m_smufl->font());
    painter->drawText(0, 0, m_char);
}
