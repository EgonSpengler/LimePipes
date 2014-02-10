/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "symbolgraphic.h"

SymbolGraphic::SymbolGraphic()
    : m_yOffset(0), m_pixmap(QPixmap())
{
}

SymbolGraphic::SymbolGraphic(qreal yOffset, const QPixmap &pixmap)
    : m_yOffset(yOffset), m_pixmap(pixmap)
{
}

qreal SymbolGraphic::yOffset() const
{
    return m_yOffset;
}

const QPixmap SymbolGraphic::pixmap() const
{
    return m_pixmap;
}

void SymbolGraphic::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
}

void SymbolGraphic::setYOffset(qreal yOffset)
{
    m_yOffset = yOffset;
}
