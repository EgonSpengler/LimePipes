/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <common/settingsobserver.h>

using namespace Settings;

class SettingsObserverTest : public QObject
{
    Q_OBJECT

public:
    SettingsObserverTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testSetGetCategory();

private:
    SettingsObserver *m_settingsObserver;
};

SettingsObserverTest::SettingsObserverTest()
    : m_settingsObserver(0)
{
}

void SettingsObserverTest::init()
{
    m_settingsObserver = new SettingsObserver();
}

void SettingsObserverTest::cleanup()
{
    delete m_settingsObserver;
}

void SettingsObserverTest::testConstructor()
{
    // Test default constructor
    delete m_settingsObserver;
    m_settingsObserver = new SettingsObserver();
    QVERIFY2(m_settingsObserver->settingCategory() == Category::NoCategory,
             "Wrong category for default constructor");

    // Test category constructor
    delete m_settingsObserver;
    m_settingsObserver = new SettingsObserver(Category::Score);
    QVERIFY2(m_settingsObserver->settingCategory() == Category::Score,
             "Wrong category for constructor");
}

void SettingsObserverTest::testSetGetCategory()
{
    Category testCategory = Category::Score;
    Q_ASSERT(m_settingsObserver->settingCategory() != testCategory);

    m_settingsObserver->setSettingsCategory(testCategory);
    QVERIFY2(m_settingsObserver->settingCategory() == testCategory,
             "Can't set/get settings category");
}

QTEST_APPLESS_MAIN(SettingsObserverTest)

#include "tst_settingsobservertest.moc"
