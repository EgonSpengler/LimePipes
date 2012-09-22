/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INSTRUMENTMANAGER_H
#define INSTRUMENTMANAGER_H

#include <QList>
#include <QString>
#include <QMap>
#include <QDir>
#include <interfaces/instrumentinterface.h>
#include <interfaces/symbolinterface.h>

#include <QDebug>

class InstrumentManager
{
public:
    explicit InstrumentManager(const QDir &pluginsDir);
    QList<QString> instrumentNames()
        { return m_instrumentPlugins.keys(); }
    int staticPluginsCount() const
        { return m_staticPlugins; }
    int dynamicPluginsCount() const
        { return m_dynamicPlugins; }
    QString pluginsPath() const
        { return m_pluginsDir.absolutePath(); }
    InstrumentPtr instrumentForName(const QString &name);
    QList<QString> symbolNamesForInstrument(const QString &instrumentName);
    Symbol *symbolForName(const QString &instrumentName, const QString &symbolName);

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
    QDir m_pluginsDir;
};

#endif // INSTRUMENTMANAGER_H
