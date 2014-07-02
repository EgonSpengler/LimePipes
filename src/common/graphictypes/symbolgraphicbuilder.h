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
#include <QObject>
#include <common/pluginmanagerinterface.h>

class GlyphItem;

class SymbolGraphicBuilder : public QObject
{
    Q_OBJECT
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

    /*! \brief graphicDataRoles Returns the data roles which affect the appearance of the graphic. */
    virtual QVector<int> graphicDataRoles() const
    {
        return QVector<int>();
    }

    int symbolType() const;
    void setSymbolType(int symbolType);

    virtual void setPluginManager(const PluginManager &pluginManager)
    {
        Q_UNUSED(pluginManager);
    }

signals:
    void dataChanged(const QVariant& data, int role);

protected:
    virtual void updateSymbolGraphic(const QVariant& value, int key)
    {
        Q_UNUSED(value);
        Q_UNUSED(key);
    }

private:
    QHash<int, QVariant> m_graphicData;
    int m_symbolType;
};

#endif // SYMBOLGRAPHICBUILDER_H
