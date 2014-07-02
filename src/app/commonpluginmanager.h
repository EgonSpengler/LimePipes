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
    explicit CommonPluginManager(QObject *parent = 0);
    explicit CommonPluginManager(const QDir& pluginsPath, QObject *parent = 0);
    ~CommonPluginManager();

    // PluginManagerInterface
    QList<SymbolMetaData> symbolMetaDatas() const;
    SymbolMetaData symbolMetaData(int type) const;

    QList<InstrumentMetaData> instrumentMetaDatas() const;
    InstrumentMetaData instrumentMetaData(int type) const;
    InstrumentMetaData instrumentMetaData(const QString &instrumentName) const;

    SymbolBehavior *symbolBehaviorForType(int type);
    QVector<int> additionalDataForSymbolType(int symbolType);
    SymbolGraphicBuilder *symbolGraphicBuilderForType(int type);
    ItemInteraction *itemInteractionForType(int type);

    QList<int> instrumentTypes() const { return m_instrumentMetaDatas.keys(); }
    QStringList instrumentNames() const;
    Instrument *instrumentForName(const QString &name) const;

    int staticPluginsCount() const { return m_staticPlugins; }
    int dynamicPluginsCount() const { return m_dynamicPlugins; }

    void setPluginsPathAndLoadDynamicPlugins(const QDir& pluginsPath);
    QString pluginsPath() const { return m_pluginsPath.absolutePath(); }

    MusicFontPtr musicFont() const;
    void setMusicFont(const MusicFontPtr &musicFont);

    PluginManager sharedPluginManager() const;
    void setSharedPluginManager(const PluginManager &sharedPluginManager);

private:
    void loadStaticPlugins();
    void loadDynamicPlugins();
    bool addInstrumentPlugin(QObject *plugin);
    void addSymbolPlugin(QObject *plugin);
    bool insertInstrumentPlugin(InstrumentInterface *instrument);
    void insertInstrumentSymbolPlugin(QObject *plugin, const QString &instrumentName);
    bool hasInstrumentWithName(const QString &name) const;
    SymbolInterface *symbolPluginWithSymbol(int symbolType);
    QMap<QString, InstrumentInterface*> m_instrumentPlugins;
    QMap<QString, SymbolInterface*> m_instrumentSymbols;
    QMap<int, SymbolMetaData> m_symbolMetaDatas;
    QMap<int, InstrumentMetaData> m_instrumentMetaDatas;
    QList<SymbolInterface*> m_symbolPlugins;
    int m_staticPlugins;
    int m_dynamicPlugins;
    QDir m_pluginsPath;
    MusicFontPtr m_musicFont;
    PluginManager m_sharedPluginManager;  // The shared pointer, that is used over all the application
};

#endif // COMMONPLUGINMANAGER_H
