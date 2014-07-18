/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class SymbolInterface
  * This is the plugin interface for Symbols.
  */

#ifndef SYMBOLINTERFACE_H
#define SYMBOLINTERFACE_H

#include <QtPlugin>
#include <QVector>
#include <QPixmap>

#include <symbol.h>
#include <common/defines.h>

class QString;
class QStringList;
class SymbolGraphicBuilder;
class ItemInteraction;

class SymbolMetaData {
public:
    SymbolMetaData()
        : m_category(SymbolCategory::None) {}
    virtual ~SymbolMetaData() {}

    bool isValid() const { return m_category != SymbolCategory::None; }

    SymbolCategory category() const { return m_category; }
    void setCategory(const SymbolCategory &category) { m_category = category; }

    QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    QPixmap iconPixmap() const { return m_iconPixmap; }
    void setIconPixmap(const QPixmap &iconPixmap) { m_iconPixmap = iconPixmap; }

private:
    QString m_name;
    SymbolCategory m_category;
    QPixmap m_iconPixmap;
};

class SymbolInterface {
public:
    virtual ~SymbolInterface() {}

    virtual SymbolMetaData symbolMetaDataForType(int type)
    {
        Q_UNUSED(type);
        return SymbolMetaData();
    }

    virtual SymbolBehavior *symbolBehaviorForType(int type) = 0;
    virtual QList<int> symbolTypes() const = 0;

    /*!
     * \brief additionalDataForSymbolType A symbol can have additional data to the symbol data
     *        e.g. melody notes have dots
     * \param symbolType The type of the symbol
     */
    virtual QVector<int> additionalDataForSymbolType(int symbolType) = 0;
    virtual SymbolGraphicBuilder *symbolGraphicBuilderForType(int type) = 0;
    virtual ItemInteraction *itemInteractionForType(int type)
    {
        Q_UNUSED(type);
        return 0;
    }
};

#define SymbolInterfaceIID "org.limepipes.LimePipes.SymbolInterface/0.2"


Q_DECLARE_INTERFACE(SymbolInterface, SymbolInterfaceIID)

#endif // SYMBOLINTERFACE_H
