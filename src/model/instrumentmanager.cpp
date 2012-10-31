/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "instrumentmanager.h"
#include <QPluginLoader>

InstrumentManager::InstrumentManager(const QDir &pluginsDir)
    : m_staticPlugins(0),
      m_dynamicPlugins(0),
      m_pluginsDir(pluginsDir)
{
    loadStaticPlugins();
    loadDynamicPlugins();
}

InstrumentPtr InstrumentManager::instrumentForName(const QString &name)
{
    InstrumentInterface *instrumentPlugin =
            m_instrumentPlugins.value(name);
    if (instrumentPlugin) {
        return instrumentPlugin->instrument();
    } else {
        return InstrumentPtr(new NullInstrument());
    }
}

QList<QString> InstrumentManager::symbolNamesForInstrument(const QString &instrumentName)
{
    if (m_instrumentSymbols.contains(instrumentName)) {
        return m_instrumentSymbols.value(instrumentName)->symbols();
    }
    return QList<QString>();
}

Symbol *InstrumentManager::symbolForName(const QString &instrumentName, const QString &symbolName)
{
    if (m_instrumentSymbols.contains(instrumentName)) {
        return m_instrumentSymbols.value(instrumentName)->getSymbol(symbolName);
    }
    return new Symbol();
}

void InstrumentManager::loadStaticPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
        if (addInstrumentPlugin(plugin)) {
            m_staticPlugins++;
        }
    }
}

void InstrumentManager::loadDynamicPlugins()
{
    if (m_pluginsDir.isReadable() == false) {
        qWarning("Plugin directory is not readable");
        return;
    }
    foreach (QString fileName, m_pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(m_pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            if (addInstrumentPlugin(plugin)) {
                m_dynamicPlugins++;
            }
        }
    }
}

bool InstrumentManager::addInstrumentPlugin(QObject *plugin)
{
    InstrumentInterface *iInstrument = qobject_cast<InstrumentInterface *> (plugin);
    if (iInstrument) {
        if (insertInstrumentPlugin(iInstrument)) {
            insertSymbolPlugin(plugin, iInstrument->name());
            return true;
        }
        return false;
    }
    return false;
}

bool InstrumentManager::insertInstrumentPlugin(InstrumentInterface *instrument)
{
    QString instrumentName = instrument->name();
    if (this->hasInstrumentWithName(instrumentName)) {
        return false;
    }
    m_instrumentPlugins.insert(instrumentName, instrument);
    return true;
}

void InstrumentManager::insertSymbolPlugin(QObject *plugin, const QString &instrumentName)
{
    SymbolInterface *iSymbols = qobject_cast<SymbolInterface *> (plugin);
    if (iSymbols) {
        m_instrumentSymbols.insert(instrumentName, iSymbols);
    }
}

bool InstrumentManager::hasInstrumentWithName(const QString &name) const
{
    return m_instrumentPlugins.keys().contains(name);
}
