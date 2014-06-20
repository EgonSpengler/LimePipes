/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPen>
#include <QGraphicsLineItem>
#include "stemglyphitem.h"

/*!
 * \brief StemGlyphItem::StemGlyphItem
 *        This is the glyph which contains the stem and the flag
 */
StemGlyphItem::StemGlyphItem()
    : m_stemDirection(Upwards),
      m_stemLengthFactor(3.5)
{
    m_flagItem = new GlyphItem(this);
    m_flagItem->connectColorRoleToGlyph(this);
    m_stemItem = new QGraphicsLineItem(this);
}

void StemGlyphItem::setLength(Length::Value length)
{
    bool hasFlag(Length::hasFlag(length));

    m_flagItem->setVisible(hasFlag);
    m_stemItem->setVisible(hasFlag);

    if (!hasFlag) {
        return;
    }

    setFlagGlyph(length);
    layoutFlagGlyphAndStem();
}

void StemGlyphItem::setPitch(const PitchPtr &pitch)
{
    layoutFlagGlyphAndStem();
}

void StemGlyphItem::setStemLengthFactor(qreal staffSpaceFactor)
{
    m_stemLengthFactor = staffSpaceFactor;
}

void StemGlyphItem::setFlagGlyph(Length::Value length)
{
    QString flagGlyphName(flagGlyphNameFromLength(length));
    m_flagItem->setGlyphName(flagGlyphName);
}

StemGlyphItem::Direction StemGlyphItem::stemDirection() const
{
    return m_stemDirection;
}

void StemGlyphItem::setStemDirection(const Direction &stemDirection)
{
    m_stemDirection = stemDirection;
}

QString StemGlyphItem::flagGlyphNameFromLength(Length::Value length)
{
    int lengthNumber = Length::toInt(length);
    QString numerator(QStringLiteral("th"));
    if (length == Length::_32) {
        numerator = QStringLiteral("nd");
    }

    QString nameTemplate("flag%1%2%3");
    QString direction = QStringLiteral("Up");
    if (m_stemDirection == Downwards) {
        direction = QStringLiteral("Down");
    }

    return nameTemplate.arg(lengthNumber).arg(numerator).arg(direction);
}

void StemGlyphItem::layoutFlagGlyphAndStem()
{
    Q_ASSERT(!musicFont().isNull());
    Q_ASSERT(parentItem());

    GlyphItem *parentGlyph = qgraphicsitem_cast<GlyphItem*>(parentItem());
    if (!parentGlyph) {
        qWarning() << "StemGlyphitem: Can't position stem to parent GlyphItem taking 0,0";
    }

    GlyphData parentData = parentGlyph->itemGlyphData();

    qreal stemLength = m_stemLengthFactor * musicFont()->staffSpace();
    QPointF basePos(parentData.stemDownNW);
    if (m_stemDirection == Upwards) {
        stemLength *= -1;
        basePos = parentData.stemUpSE;
    }

    qreal halfLineThickness = m_stemItem->pen().widthF() / 2;
    m_stemItem->setLine(halfLineThickness, 0,
                        halfLineThickness, stemLength);
    m_stemItem->setPos(basePos);

    m_flagItem->setPos(QPointF(0, stemLength) + basePos);
}

void StemGlyphItem::musicFontHasChanged(const MusicFontPtr &musicFont)
{
    QPen stemPen = m_stemItem->pen();
    stemPen.setWidthF(musicFont->engravings().stemThickness *
                      musicFont->staffSpace());
    m_stemItem->setPen(stemPen);
}

void StemGlyphItem::colorRoleHasChanged(const FontColor &colorRole)
{
    QPen stemPen = m_stemItem->pen();
    stemPen.setColor(musicFont()->fontColor(colorRole));
    m_stemItem->setPen(stemPen);
}
