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
        foreach (const int type, iSymbols->symbolTypes()) {
            SymbolMetaData metaData = iSymbols->symbolMetaDataForType(type);
            if (metaData.isValid()) {
                m_symbolMetaDatas.insert(type, metaData);
            }
        }
    }
}

bool CommonPluginManager::insertInstrumentPlugin(InstrumentInterface *instrument)
{
    InstrumentMetaData instrumentMeta = instrument->instrumentMetaData();
    int instrumentType = instrument->type();
    if (m_instrumentMetaDatas.contains(instrumentType))
        return false;

    m_instrumentMetaDatas.insert(instrumentType, instrumentMeta);

    // TODO Still necessary to keep InstrumentInterface pointers?
    QString instrumentName = instrumentMeta.name();
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

MusicFontPtr CommonPluginManager::musicFont() const
{
    return m_musicFont;
}

void CommonPluginManager::setMusicFont(const MusicFontPtr &musicFont)
{
    m_musicFont = musicFont;
}

SymbolGraphicBuilder *CommonPluginManager::symbolGraphicBuilderForType(int type)
{
    SymbolInterface *symbolPlugin = symbolPluginWithSymbol(type);
    if (!symbolPlugin)
        return 0;

    SymbolGraphicBuilder *builder = symbolPlugin->symbolGraphicBuilderForType(type);
    if (builder) {
        builder->setPluginManager(m_sharedPluginManager);
        builder->setSymbolType(type);
    }

    return builder;
}

ItemInteraction *CommonPluginManager::itemInteractionForType(int type)
{
    SymbolInterface *symbolPlugin = symbolPluginWithSymbol(type);
    if (!symbolPlugin)
        return 0;

    return symbolPlugin->itemInteractionForType(type);
}

QStringList CommonPluginManager::instrumentNames() const
{
    QStringList names;
    foreach (const InstrumentMetaData metaData, m_instrumentMetaDatas) {
        names << metaData.name();
    }

    return names;
}

SymbolBehavior *CommonPluginManager::symbolBehaviorForType(int type)
{
    SymbolInterface *symbolPlugin = symbolPluginWithSymbol(type);
    if (!symbolPlugin)
        return 0;

    return symbolPlugin->symbolBehaviorForType(type);
}

QVector<int> CommonPluginManager::additionalDataForSymbolType(int symbolType)
{
    SymbolInterface *symbolPlugin = symbolPluginWithSymbol(symbolType);
    if (!symbolPlugin)
        return QVector<int>();

    return symbolPlugin->additionalDataForSymbolType(symbolType);
}

SymbolInterface *CommonPluginManager::symbolPluginWithSymbol(int symbolType)
{
    foreach (SymbolInterface *symbolPlugin, m_symbolPlugins) {
        if (!symbolPlugin)
            continue;

        QList<int> symbolTypes(symbolPlugin->symbolTypes());

        if (symbolTypes.contains(symbolType)) {
            SymbolMetaData symbolMeta = symbolPlugin->symbolMetaDataForType(symbolType);
            if (symbolMeta.isValid()) {
                return symbolPlugin;
            }
        }
    }

    return 0;
}
PluginManager CommonPluginManager::sharedPluginManager() const
{
    return m_sharedPluginManager;
}

void CommonPluginManager::setSharedPluginManager(const PluginManager &pluginManager)
{
    m_sharedPluginManager = pluginManager;
}


QList<SymbolMetaData> CommonPluginManager::symbolMetaDatas() const
{
    return m_symbolMetaDatas.values();
}

SymbolMetaData CommonPluginManager::symbolMetaData(int type) const
{
    return m_symbolMetaDatas.value(type);
}

QList<InstrumentMetaData> CommonPluginManager::instrumentMetaDatas() const
{
    return m_instrumentMetaDatas.values();
}

InstrumentMetaData CommonPluginManager::instrumentMetaData(int type) const
{
    return m_instrumentMetaDatas.value(type);
}

InstrumentMetaData CommonPluginManager::instrumentMetaData(const QString &instrumentName) const
{
    foreach (const int type, m_instrumentMetaDatas.keys()) {
        InstrumentMetaData metaData = instrumentMetaData(type);
        if (metaData.name() == instrumentName) {
            return metaData;
        }
    }

    return InstrumentMetaData();
}
