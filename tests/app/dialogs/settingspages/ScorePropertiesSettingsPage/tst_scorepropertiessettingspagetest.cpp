/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <app/dialogs/settingspages/scorepropertiessettingspage.h>

class ScorePropertiesSettingsPageTest : public QObject
{
    Q_OBJECT

public:
    ScorePropertiesSettingsPageTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testCase1();

private:
    ScorePropertiesSettingsPage *m_scoreSettingsPage;
};

ScorePropertiesSettingsPageTest::ScorePropertiesSettingsPageTest()
    : m_scoreSettingsPage(0)
{
}

void ScorePropertiesSettingsPageTest::init()
{
    m_scoreSettingsPage = new ScorePropertiesSettingsPage();
}

void ScorePropertiesSettingsPageTest::cleanup()
{
    delete m_scoreSettingsPage;
}

void ScorePropertiesSettingsPageTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(ScorePropertiesSettingsPageTest)

#include "tst_scorepropertiessettingspagetest.moc"
