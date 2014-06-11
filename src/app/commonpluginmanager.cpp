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
#include <common/graphicsmapperinterface.h>
#include <common/datatypes/instrument.h>
#include "commonpluginmanager.h"

CommonPluginManager::CommonPluginManager(QObject *parent)
    : QObject(parent),
      m_staticPlugins(0),
      m_dynamicPlugins(0),
      m_graphicsMapper(0)
{
    loadStaticPlugins();
}

CommonPluginManager::CommonPluginManager(const QDir &pluginsPath, QObject *parent)
    : QObject(parent),
      m_staticPlugins(0),
      m_dynamicPlugins(0),
      m_pluginsPath(pluginsPath),
      m_graphicsMapper(0)
{
    loadStaticPlugins();
    loadDynamicPlugins();
}

CommonPluginManager::~CommonPluginManager()
{
}

QVector<int> CommonPluginManager::symbolTypesForInstrument(const QString &instrumentName) const
{
    if (m_instrumentSymbols.contains(instrumentName)) {
        return m_instrumentSymbols.value(instrumentName)->symbolTypes();
    }
    return QVector<int>();
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
        builder->setMusicFont(m_musicFont);
        builder->setGraphicsMapper(m_graphicsMapper);
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

Symbol *CommonPluginManager::symbolForType(int type)
{
    SymbolInterface *symbolPlugin = symbolPluginWithSymbol(type);
    if (!symbolPlugin)
        return 0;

    return symbolPlugin->symbolForType(type);
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

        QVector<int> symbolTypes(symbolPlugin->symbolTypes());

        if (symbolTypes.contains(symbolType)) {
            Symbol *symbol = symbolPlugin->symbolForType(symbolType);
            if (symbol != 0) {
                delete symbol;
                return symbolPlugin;
            }
        }
    }

    return 0;
}

GraphicsMapperInterface *CommonPluginManager::graphicsMapper() const
{
    return m_graphicsMapper;
}

void CommonPluginManager::setGraphicsMapper(GraphicsMapperInterface *graphicsMapper)
{
    m_graphicsMapper = graphicsMapper;
}
