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
#include <common/graphictypes/SMuFL/smufl.h>

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

    SMuFLPtr smufl() const { return m_smufl; }
    void setSmufl(const SMuFLPtr &smufl)
    {
        m_smufl = smufl;
        smuflChanged(m_smufl);
    }

    /*! \brief graphicDataRoles Returns the data roles which affect the appearance of the graphic. */
    virtual QVector<int> graphicDataRoles() const
    {
        return QVector<int>();
    }

protected:
    virtual void updateSymbolGraphic(const QVariant& value, int key)
    {
        Q_UNUSED(value);
        Q_UNUSED(key);
    }

    virtual void smuflChanged(const SMuFLPtr &smufl) { Q_UNUSED(smufl); }

private:
    QHash<int, QVariant> m_graphicData;
    SMuFLPtr m_smufl;
};

#endif // SYMBOLGRAPHICBUILDER_H
