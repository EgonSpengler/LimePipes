/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPluginLoader>
#include <common/graphictypes/symbolgraphicbuilder.h>
#include <common/interfaces/symbolinterface.h>
#include <common/interfaces/instrumentinterface.h>
#include <common/datatypes/instrument.h>
#include "commonpluginmanager.h"

CommonPluginManager::CommonPluginManager(QObject *parent)
    : QObject(parent),
      m_staticPlugins(0),
      m_dynamicPlugins(0)
{
    loadStaticPlugins();
}

CommonPluginManager::CommonPluginManager(const QDir &pluginsPath, QObject *parent)
    : QObject(parent),
      m_staticPlugins(0),
      m_dynamicPlugins(0),
      m_pluginsPath(pluginsPath)
{
    loadStaticPlugins();
    loadDynamicPlugins();
}

CommonPluginManager::~CommonPluginManager()
{
}

QStringList CommonPluginManager::symbolNamesForInstrument(const QString &instrumentName) const
{
    if (m_instrumentSymbols.contains(instrumentName)) {
        return m_instrumentSymbols.value(instrumentName)->symbolNames();
    }
    return QStringList();
}

QVector<int> CommonPluginManager::symbolTypesForInstrument(const QString &instrumentName) const
{
    if (m_instrumentSymbols.contains(instrumentName)) {
        return m_instrumentSymbols.value(instrumentName)->symbolTypes();
    }
    return QVector<int>();
}

Symbol *CommonPluginManager::symbolForName(const QString &instrumentName, const QString &symbolName) const
{
    if (m_instrumentSymbols.contains(instrumentName)) {
        if (m_instrumentSymbols.value(instrumentName)->symbolNames().contains(symbolName))
            return m_instrumentSymbols.value(instrumentName)->getSymbolForName(symbolName);
    }
    return new Symbol();
}

Instrument *CommonPluginManager::instrumentForName(const QString &name) const
{
    InstrumentInterface *instrumentPlugin = m_instrumentPlugins.value(name);
    if (instrumentPlugin) {
        return instrumentPlugin->instrument();
    } else {
        return new NullInstrument();
    }
}

void CommonPluginManager::setPluginsPathAndLoadDynamicPlugins(const QDir &pluginsPath)
{
    m_pluginsPath = pluginsPath;

    loadDynamicPlugins();
}

void CommonPluginManager::loadStaticPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
        if (addInstrumentPlugin(plugin)) {
            m_staticPlugins++;
        }
        addSymbolPlugin(plugin);
    }
}

void CommonPluginManager::loadDynamicPlugins()
{
    if (m_pluginsPath.isReadable() == false) {
        qWarning("Plugin directory is not readable");
        return;
    }
    foreach (QString fileName, m_pluginsPath.entryList(QDir::Files)) {
        QPluginLoader loader(m_pluginsPath.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            if (addInstrumentPlugin(plugin)) {
                m_dynamicPlugins++;
            }
            addSymbolPlugin(plugin);
        }
    }
}

bool CommonPluginManager::addInstrumentPlugin(QObject *plugin)
{
    InstrumentInterface *iInstrument = qobject_cast<InstrumentInterface *> (plugin);
    if (iInstrument) {
        if (insertInstrumentPlugin(iInstrument)) {
            insertInstrumentSymbolPlugin(plugin, iInstrument->name());
            return true;
        }
        return false;
    }
    return false;
}

void CommonPluginManager::addSymbolPlugin(QObject *plugin)
{
    SymbolInterface *iSymbols = qobject_cast<SymbolInterface *> (plugin);
    if (iSymbols) {
        m_symbolPlugins.append(iSymbols);
    }
}

bool CommonPluginManager::insertInstrumentPlugin(InstrumentInterface *instrument)
{
    QString instrumentName = instrument->name();
    if (this->hasInstrumentWithName(instrumentName)) {
        return false;
    }
    m_instrumentPlugins.insert(instrumentName, instrument);
    return true;
}

void CommonPluginManager::insertInstrumentSymbolPlugin(QObject *plugin, const QString &instrumentName)
{
    SymbolInterface *iSymbols = qobject_cast<SymbolInterface *> (plugin);
    if (iSymbols) {
        m_instrumentSymbols.insert(instrumentName, iSymbols);
    }
}

bool CommonPluginManager::hasInstrumentWithName(const QString &name) const
{
    return m_instrumentPlugins.keys().contains(name);
}
SMuFLPtr CommonPluginManager::smufl() const
{
    return m_smufl;
}

void CommonPluginManager::setSmufl(const SMuFLPtr &smufl)
{
    m_smufl = smufl;
}

SymbolGraphicBuilder *CommonPluginManager::symbolGraphicBuilderForType(int type)
{
    foreach (SymbolInterface *symbolPlugin, m_symbolPlugins) {
        if (!symbolPlugin)
            continue;

        SymbolGraphicBuilder *builder = symbolPlugin->symbolGraphicBuilderForType(type);
        if (builder) {
            builder->setSmufl(m_smufl);
            return builder;
        }
    }

    return 0;
}

ItemInteraction *CommonPluginManager::itemInteractionForType(int type)
{
    foreach (SymbolInterface *symbolPlugin, m_symbolPlugins) {
        if (!symbolPlugin)
            continue;

        ItemInteraction *interaction = symbolPlugin->itemInteractionForType(type);
        if (interaction) {
            return interaction;
        }
    }

    return 0;
}

Symbol *CommonPluginManager::symbolForType(int type)
{
    foreach (SymbolInterface *symbolPlugin, m_symbolPlugins) {
        if (!symbolPlugin)
            continue;

        QVector<int> symbolTypes(symbolPlugin->symbolTypes());

        if (symbolTypes.contains(type)) {
            Symbol *symbol = symbolPlugin->symbolForType(type);
            if (symbol == 0)
                continue;

            return symbol;
        }
    }

    return 0;
}

