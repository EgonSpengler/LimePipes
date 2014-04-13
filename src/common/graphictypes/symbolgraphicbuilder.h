/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICBUILDER_H
#define SYMBOLGRAPHICBUILDER_H

#include <QHash>
#include <QVector>
#include <QVariant>
#include "symbolgraphic.h"

class GlyphItem;

class SymbolGraphicBuilder
{
    friend class SymbolGraphicBuilderTest;
public:
    explicit SymbolGraphicBuilder();
    virtual ~SymbolGraphicBuilder() {}

    /*!
     * \brief glyphItem Return the GlyphItem which represents the Symbol
     */
    virtual GlyphItem *glyphItem() const;

    void setData(const QVariant &value, int key);
    QVariant data(int key) const;

protected:
    void setSymbolGraphicPixmap(const QPixmap &pixmap);
    void setSymbolGraphicYOffset(qreal yOffset);

    virtual void updateSymbolGraphic(const QVariant& value, int key)
    {
        Q_UNUSED(value);
        Q_UNUSED(key);
    }

    /*! \brief graphicDataRoles Returns the data roles which affect the appearance of the graphic. */
    virtual QVector<int> graphicDataRoles() const
    {
        return QVector<int>();
    }

private:
    void initSymbolGraphicMember();
    SymbolGraphicPtr m_graphic;
    QHash<int, QVariant> m_graphicData;
};

#endif // SYMBOLGRAPHICBUILDER_H
