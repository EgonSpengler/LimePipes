/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */
#ifndef __INSTRUMENTMANAGERTEST_H__
#define __INSTRUMENTMANAGERTEST_H__

#include <QObject>

class InstrumentManager;
class QDir;

class InstrumentManagerTest : public QObject
{
    Q_OBJECT

public:
    InstrumentManagerTest()
        : m_staticInstrumentPlugins(0),
          m_dynamicInstrumentPlugins(0),
          m_pluginsWithDoubleName(0),
          m_pluginsPath(0),
          m_manager(0)
    {}
    ~InstrumentManagerTest()
    { delete m_manager, delete m_pluginsPath; }

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testPreconditions();
    void testPluginsWereLoaded();
    void testLoadedStaticPlugins();
    void testPluginsPath();
    void testLoadedDynamicPlugins();
    void testInstrumentForName();
    void testInstrumentNames();
    void testSymbolNamesForInstrument();
    void testGetSymbolByName();

private:
    void loadStaticPlugins();
    void loadDynamicPlugins();
    void setPluginsPath();
    void insertPluginIfInstrument(QObject *plugin, bool isStaticPlugin);
    void insertPluginName(const QString &name, bool isStaticPlugin);
    QList<QString> getSymbolNamesFromInstrumentName(const QString &instrumentName);
    int m_staticInstrumentPlugins;
    int m_dynamicInstrumentPlugins;
    int m_pluginsWithDoubleName;
    QDir *m_pluginsPath;
    QList<QString> m_instrumentPluginNames;
    InstrumentManager *m_manager;
    QList<QString> m_managerInstrumentNames;
};

#endif

