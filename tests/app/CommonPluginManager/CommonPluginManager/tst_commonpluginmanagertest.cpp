/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QDebug>
#include <app/commonpluginmanager.h>
#include <common/datatypes/instrument.h>
#include <common/pluginmanagerinterface.h>
#include <common/interfaces/instrumentinterface.h>
#include <common/interfaces/symbolinterface.h>

Q_IMPORT_PLUGIN(GreatHighlandBagpipe)

class CommonPluginManagerTest : public QObject
{
    Q_OBJECT

public:
    CommonPluginManagerTest();

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
    QStringList getSymbolNamesFromInstrumentName(const QString &instrumentName);
    int m_staticInstrumentPlugins;
    int m_dynamicInstrumentPlugins;
    int m_pluginsWithDoubleName;
    QDir m_pluginsPath;
    QStringList m_instrumentPluginNames;
    CommonPluginManager *m_commonPluginManager;
    QStringList m_managerInstrumentNames;
};

CommonPluginManagerTest::CommonPluginManagerTest()
    : m_staticInstrumentPlugins(0),
      m_dynamicInstrumentPlugins(0),
      m_pluginsWithDoubleName(0),
      m_pluginsPath(0)
{
}

void CommonPluginManagerTest::initTestCase()
{
    qDebug() << "Score title" << LP::ScoreTitle;
    qDebug() << "Symbol type" << LP::SymbolType;
    qDebug() << "Symbol name" << LP::SymbolName;

    loadStaticPlugins();
    loadDynamicPlugins();

    m_commonPluginManager = new CommonPluginManager(m_pluginsPath, this);
    m_managerInstrumentNames = m_commonPluginManager->instrumentNames();
}

void CommonPluginManagerTest::cleanupTestCase()
{
}

void CommonPluginManagerTest::testPreconditions()
{
    QVERIFY2(m_staticInstrumentPlugins > 0, "No static plugins for this test");
    QVERIFY2(m_dynamicInstrumentPlugins > 0, "No dynamic plugins for this test");
    QVERIFY2(m_pluginsWithDoubleName > 0, "No Plugins with double names for this test");
}

void CommonPluginManagerTest::testPluginsWereLoaded()
{
    QVERIFY2(m_managerInstrumentNames.count() != 0, "No Plugin was loaded");
}

void CommonPluginManagerTest::testLoadedStaticPlugins()
{
    QVERIFY2(m_commonPluginManager->staticPluginsCount() == m_staticInstrumentPlugins, "Not the correct amount of static plugins loaded");
}

void CommonPluginManagerTest::testPluginsPath()
{
    QVERIFY2(m_commonPluginManager->pluginsPath() == m_pluginsPath.absolutePath(), "The plugins path does not match");
}

void CommonPluginManagerTest::testLoadedDynamicPlugins()
{
    QVERIFY2(m_commonPluginManager->dynamicPluginsCount() != m_dynamicInstrumentPlugins + m_pluginsWithDoubleName, "Plugin Manager loaded double instrument plugins");
    QVERIFY2(m_commonPluginManager->dynamicPluginsCount() == m_dynamicInstrumentPlugins, "Not the correct amount of dynamic plugins loaded.");
}

void CommonPluginManagerTest::testInstrumentForName()
{
    Q_ASSERT(m_instrumentPluginNames.count() > 0);
    QString instrumentName = m_instrumentPluginNames.at(0);
    InstrumentPtr instrument = InstrumentPtr(m_commonPluginManager->instrumentForName(instrumentName));

    QVERIFY2(instrument->name() == instrumentName, "Failed getting instrument for name");
}

void CommonPluginManagerTest::testInstrumentNames()
{
    QList<QString> managerPluginNames(m_commonPluginManager->instrumentNames());
    QVERIFY2(managerPluginNames.count() == m_instrumentPluginNames.count(),
             "InstrumentManager hasn't loaded the same amount of isntruments");
    foreach (QString instrument, m_instrumentPluginNames) {
        QVERIFY2(managerPluginNames.contains(instrument), "InstrumentManager contains not that instrument");
    }
}

void CommonPluginManagerTest::testSymbolNamesForInstrument()
{
    QString instrumentName = "Great Highland Bagpipe";
    QList<QString> symbolNames = getSymbolNamesFromInstrumentName(instrumentName);
    int symbolCountFromManager = m_commonPluginManager->symbolNamesForInstrument(instrumentName).count();
    QVERIFY2(symbolCountFromManager == symbolNames.count(), "Instrument Manager returns not the same amount of symbol names");
}

void CommonPluginManagerTest::testGetSymbolByName()
{
    QString instrumentName = "Great Highland Bagpipe";
    QList<QString> allSymbolNamesForInstrument = getSymbolNamesFromInstrumentName(instrumentName);
    Symbol *symbol;
    QList<QString>::iterator i;
    for (i = allSymbolNamesForInstrument.begin(); i != allSymbolNamesForInstrument.end(); ++i) {
        QString symbolName(*i);
        symbol = m_commonPluginManager->symbolForName(instrumentName, symbolName);
        QString symbolNameFromData(symbol->data(LP::SymbolName).toString());
        QVERIFY2(symbolName == symbolNameFromData, "Got the wrong symbol");
    }
}

void CommonPluginManagerTest::loadStaticPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
        insertPluginIfInstrument(plugin, true);
    }
}

void CommonPluginManagerTest::loadDynamicPlugins()
{
    setPluginsPath();
    foreach (QString fileName, m_pluginsPath.entryList(QDir::Files)) {
        QPluginLoader loader(m_pluginsPath.absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            insertPluginIfInstrument(plugin, false);
        }
    }
}

void CommonPluginManagerTest::setPluginsPath()
{
    m_pluginsPath = QDir(qApp->applicationDirPath());
    m_pluginsPath.cd("plugins");
}

void CommonPluginManagerTest::insertPluginIfInstrument(QObject *plugin, bool isStaticPlugin)
{
    InstrumentInterface *iInstrument = qobject_cast<InstrumentInterface *> (plugin);
    if (iInstrument) {
        insertPluginName(iInstrument->name(), isStaticPlugin);
    }
}

void CommonPluginManagerTest::insertPluginName(const QString &name, bool isStaticPlugin)
{
    if (m_instrumentPluginNames.contains(name)) {
        m_pluginsWithDoubleName++;
        return;
    }

    m_instrumentPluginNames.insert(0, name);

    if (isStaticPlugin) {
        m_staticInstrumentPlugins++;
    } else {
        m_dynamicInstrumentPlugins++;
    }
}

QStringList CommonPluginManagerTest::getSymbolNamesFromInstrumentName(const QString &instrumentName)
{
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
        InstrumentInterface *iInstrument = qobject_cast<InstrumentInterface *> (plugin);
        if (iInstrument) {
            if (iInstrument->name() == instrumentName) {
                SymbolInterface *iSymbols = qobject_cast<SymbolInterface *> (plugin);
                if (iSymbols) {
                    return iSymbols->symbols();
                }
            }
        }
    }
    return QStringList();
}

QTEST_MAIN(CommonPluginManagerTest)

#include "tst_commonpluginmanagertest.moc"
