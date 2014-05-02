/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ABSTRACTVISUALITEMFACTORY_H
#define ABSTRACTVISUALITEMFACTORY_H

#include <common/pluginmanagerinterface.h>
#include "visualitem.h"

class AbstractVisualItemFactory
{
public:
    explicit AbstractVisualItemFactory() {}
    virtual ~AbstractVisualItemFactory() {}

    virtual VisualItem *createVisualItem(VisualItem::ItemType type) = 0;
    virtual VisualItem *createVisualSymbol(int symbolType) = 0;

    void setPluginManager(PluginManager pluginManager) { m_pluginManager = pluginManager; }
    PluginManager pluginManger() const { return m_pluginManager; }
    bool hasValidPluginManager() const { return !m_pluginManager.isNull(); }

private:
    PluginManager m_pluginManager;
};

#endif // ABSTRACTVISUALITEMFACTORY_H
