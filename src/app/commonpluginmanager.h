/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef COMMONPLUGINMANAGER_H
#define COMMONPLUGINMANAGER_H

#include <QDir>
#include <QMap>
#include <QStringList>
#include <QObject>
#include <common/pluginmanagerinterface.h>

class SymbolInterface;
class InstrumentInterface;

class CommonPluginManager : public QObject,
                            public PluginManagerInterface
{
    Q_OBJECT
public:
    explicit CommonPluginManager(const QDir& pluginsPath, QObject *parent = 0);

    // PluginManagerInterface
    QStringList symbolNamesForInstrument(const QString &instrumentName) const;
    Symbol *symbolForName(const QString &instrumentName, const QString &symbolName) const;

    QStringList instrumentNames() const { return m_instrumentPlugins.keys(); }
    Instrument *instrumentForName(const QString &name) const;

    int staticPluginsCount() const { return m_staticPlugins; }
    int dynamicPluginsCount() const { return m_dynamicPlugins; }

    void setPluginsPathAndLoadDynamicPlugins(const QDir& pluginsPath);
    QString pluginsPath() const { return m_pluginsPath.absolutePath(); }

private:
    void loadStaticPlugins();
    void loadDynamicPlugins();
    bool addInstrumentPlugin(QObject *plugin);
    bool insertInstrumentPlugin(InstrumentInterface *instrument);
    void insertSymbolPlugin(QObject *plugin, const QString &instrumentName);
    bool hasInstrumentWithName(const QString &name) const;
    QMap<QString, InstrumentInterface*> m_instrumentPlugins;
    QMap<QString, SymbolInterface*> m_instrumentSymbols;
    int m_staticPlugins;
    int m_dynamicPlugins;
    QDir m_pluginsPath;
};

#endif // COMMONPLUGINMANAGER_H
