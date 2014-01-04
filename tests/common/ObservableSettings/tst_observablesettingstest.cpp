/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <common/observablesettings.h>
#include <testsettingsobserver.h>

#include <QDebug>

using namespace Settings;

class ObservableSettingsTest : public QObject
{
    Q_OBJECT

public:
    ObservableSettingsTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testRegisterObserver();
    void testUnregisterObserver();
    void testNotifyCategory();
    void testNotifyOnAlreadyDeletedObserver();
};

ObservableSettingsTest::ObservableSettingsTest()
{
}

void ObservableSettingsTest::init()
{
    ObservableSettings::m_settingsObserver.clear();
}

void ObservableSettingsTest::cleanup()
{
}

void ObservableSettingsTest::testRegisterObserver()
{
    Q_ASSERT(ObservableSettings::m_settingsObserver.count() == 0);

    TestSettingsObserver *testObserver = new TestSettingsObserver(this);
    testObserver->setSettingsCategory(Category::NoCategory);
    ObservableSettings::registerObserver(testObserver);
    QVERIFY2(ObservableSettings::m_settingsObserver.count() == 0,
             "Observer was registered despite no settings category");

    testObserver->setSettingsCategory(Category::Score);
    ObservableSettings::registerObserver(testObserver);
    QVERIFY2(ObservableSettings::m_settingsObserver.count() == 1,
             "Observer wasn't registered.");
}

void ObservableSettingsTest::testUnregisterObserver()
{
    Q_ASSERT(ObservableSettings::m_settingsObserver.count() == 0);

    ObservableSettings::m_settingsObserver.clear();
    Q_ASSERT(ObservableSettings::m_settingsObserver.count() == 0);

    TestSettingsObserver *testObserver = new TestSettingsObserver(this);
    testObserver->setSettingsCategory(Category::Score);
    ObservableSettings::registerObserver(testObserver);
    Q_ASSERT(ObservableSettings::m_settingsObserver.count());

    ObservableSettings::unregisterObserver(testObserver);
    QVERIFY2(ObservableSettings::m_settingsObserver.count() == 0,
             "Observer wasn't unregistered");

    delete testObserver;
}

void ObservableSettingsTest::testNotifyCategory()
{
    Q_ASSERT(ObservableSettings::m_settingsObserver.count() == 0);

    TestSettingsObserver *testObserverScoreSettings = new TestSettingsObserver();
    testObserverScoreSettings->setSettingsCategory(Category::Score);
    TestSettingsObserver *testObserverTuneSettings = new TestSettingsObserver();
    testObserverTuneSettings->setSettingsCategory(Category::Tune);

    QSignalSpy scoreSpy(testObserverScoreSettings, SIGNAL(notifyCalled()));
    QSignalSpy tuneSpy(testObserverTuneSettings, SIGNAL(notifyCalled()));

    ObservableSettings::registerObserver(testObserverScoreSettings);
    ObservableSettings::registerObserver(testObserverTuneSettings);

    Q_ASSERT(ObservableSettings::m_settingsObserver.count() == 2);

    ObservableSettings::notify(Category::Score);

    QVERIFY2(scoreSpy.count() == 1,
             "Notify wasn't called on settings observer");
    QVERIFY2(tuneSpy.count() == 0,
             "Notify was called on observer with wrong category");

    delete testObserverScoreSettings;
    delete testObserverTuneSettings;
}

void ObservableSettingsTest::testNotifyOnAlreadyDeletedObserver()
{
    Q_ASSERT(ObservableSettings::m_settingsObserver.count() == 0);

    TestSettingsObserver *testObserverScoreSettings = new TestSettingsObserver();
    testObserverScoreSettings->setSettingsCategory(Category::Score);
    ObservableSettings::registerObserver(testObserverScoreSettings);

    delete testObserverScoreSettings;

    Q_ASSERT(ObservableSettings::m_settingsObserver.count() == 1);

    ObservableSettings::notify(Category::Score);

    QVERIFY2(ObservableSettings::m_settingsObserver.count() == 0,
             "Already deleted observer wasn't removed");
}

QTEST_APPLESS_MAIN(ObservableSettingsTest)

#include "tst_observablesettingstest.moc"
