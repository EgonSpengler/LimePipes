/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QList>
#include <QString>
#include <QDir>
#include <QPluginLoader>
#include <instrumentinterface.h>
#include <symbolinterface.h>
#include <app/instrumentmanager.h>

Q_IMPORT_PLUGIN(lp_greathighlandbagpipe)

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

void InstrumentManagerTest::initTestCase()
{
    loadStaticPlugins();
    loadDynamicPlugins();

    m_manager = new InstrumentManager(*m_pluginsPath);
    m_managerInstrumentNames = m_manager->instrumentNames();
}

void InstrumentManagerTest::cleanupTestCase()
{
    delete m_manager;
}

void InstrumentManagerTest::testPreconditions()
{
    QVERIFY2(m_staticInstrumentPlugins > 0, "No static plugins for this test");
    QVERIFY2(m_dynamicInstrumentPlugins > 0, "No dynamic plugins for this test");
    QVERIFY2(m_pluginsWithDoubleName > 0, "No Plugins with double names for this test");
}

void InstrumentManagerTest::testPluginsWereLoaded()
{
    QVERIFY2(m_managerInstrumentNames.count() != 0, "No Plugin was loaded");
}

void InstrumentManagerTest::testLoadedStaticPlugins()
{
    QVERIFY2(m_manager->staticPluginsCount() == m_staticInstrumentPlugins, "Not the correct amount of static plugins loaded");
}

void InstrumentManagerTest::testPluginsPath()
{
    QVERIFY2(m_manager->pluginsPath() == m_pluginsPath->absolutePath(), "The plugins path does not match");
}

void InstrumentManagerTest::testLoadedDynamicPlugins()
{
    QVERIFY2(m_manager->dynamicPluginsCount() != m_dynamicInstrumentPlugins + m_pluginsWithDoubleName, "Plugin Manager loaded double instrument plugins");
    QVERIFY2(m_manager->dynamicPluginsCount() == m_dynamicInstrumentPlugins, "Not the correct amount of dynamic plugins loaded.");
}

void InstrumentManagerTest::testInstrumentForName()
{
    Q_ASSERT(m_instrumentPluginNames.count() > 0);
    QString instrumentName = m_instrumentPluginNames.at(0);
    InstrumentPtr instrument = m_manager->instrumentForName(instrumentName);

    QVERIFY2(instrument->name() == instrumentName, "Failed getting instrument for name");
}

void InstrumentManagerTest::testInstrumentNames()
{
    QList<QString> managerPluginNames(m_manager->instrumentNames());
    QVERIFY2(managerPluginNames.count() == m_instrumentPluginNames.count(),
             "InstrumentManager hasn't loaded the same amount of isntruments");
    foreach (QString instrument, m_instrumentPluginNames) {
        QVERIFY2(managerPluginNames.contains(instrument), "InstrumentManager contains not that instrument");
    }
}

void InstrumentManagerTest::testSymbolNamesForInstrument()
{
    QString instrumentName = "Great Highland Bagpipe";
    QList<QString> symbolNames = getSymbolNamesFromInstrumentName(instrumentName);
    int symbolCountFromManager = m_manager->symbolNamesForInstrument(instrumentName).count();
    QVERIFY2(symbolCountFromManager == symbolNames.count(), "Instrument Manager returns not the same amount of symbol names");
}

void InstrumentManagerTest::testGetSymbolByName()
{
    QString instrumentName = "Great Highland Bagpipe";
    QList<QString> symbolNames = getSymbolNamesFromInstrumentName(instrumentName);
    Symbol *symbol;
    QList<QString>::iterator i;
    for (i = symbolNames.begin(); i != symbolNames.end(); ++i) {
        symbol = m_manager->symbolForName(instrumentName, *i);
        QVERIFY2(symbol->data(LP::symbolName) == *i, "Got the wrong symbol");
    }
}

void InstrumentManagerTest::loadStaticPlugins()
{
    foreach (QObject *plugin, QPluginLoader::staticInstances()) {
        insertPluginIfInstrument(plugin, true);
    }
}

void InstrumentManagerTest::loadDynamicPlugins()
{
    setPluginsPath();
    foreach (QString fileName, m_pluginsPath->entryList(QDir::Files)) {
        QPluginLoader loader(m_pluginsPath->absoluteFilePath(fileName));
        QObject *plugin = loader.instance();
        if (plugin) {
            insertPluginIfInstrument(plugin, false);
        }
    }
}

void InstrumentManagerTest::setPluginsPath()
{
    if (m_pluginsPath) {
        delete m_pluginsPath;
    }
    m_pluginsPath = new QDir(qApp->applicationDirPath());
    m_pluginsPath->cd("plugins");
}

void InstrumentManagerTest::insertPluginIfInstrument(QObject *plugin, bool isStaticPlugin)
{
    InstrumentInterface *iInstrument = qobject_cast<InstrumentInterface *> (plugin);
    if (iInstrument) {
        insertPluginName(iInstrument->name(), isStaticPlugin);
    }
}

void InstrumentManagerTest::insertPluginName(const QString&name, bool isStaticPlugin)
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

QList<QString> InstrumentManagerTest::getSymbolNamesFromInstrumentName(const QString &instrumentName)
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
    return QList<QString>();
}

QTEST_MAIN(InstrumentManagerTest)

#include "tst_instrumentmanagertest.moc"
