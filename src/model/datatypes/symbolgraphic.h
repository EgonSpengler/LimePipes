/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHIC_H
#define SYMBOLGRAPHIC_H

#include <QMetaType>
#include <QPixmap>
#include <QSharedPointer>

class SymbolGraphic
{
    friend class SymbolGraphicBuilder;
public:
    explicit SymbolGraphic();
    explicit SymbolGraphic(qreal yOffset, const QPixmap &pixmap);

    qreal yOffset() const;
    const QPixmap pixmap() const;

private:
    void setPixmap(const QPixmap &pixmap);
    void setYOffset(qreal yOffset);
    qreal m_yOffset;
    QPixmap m_pixmap;
};

typedef QSharedPointer<SymbolGraphic> SymbolGraphicPtr;

Q_DECLARE_METATYPE(SymbolGraphicPtr)

#endif // SYMBOLGRAPHIC_H
