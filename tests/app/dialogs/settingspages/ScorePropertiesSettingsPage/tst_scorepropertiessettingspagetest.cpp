/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <common/scoresettings.h>
#include <app/dialogs/settingspages/scorepropertiessettingspage.h>
#include <app/dialogs/settingspages/scorepropertieswidget.h>

#include <QDebug>

using namespace Settings;
using namespace Settings::Score;

class ScorePropertiesSettingsPageTest : public QObject
{
    Q_OBJECT

public:
    ScorePropertiesSettingsPageTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetScoreArea();
    void testPropertyWidgetDefaultValuesFromSettings();
    void testPropertyWidgetValuesFromSettings();

private:
    void testPropertiesWidget(Area area, LP::ScoreDataRole testDataRole);
    void clearSettings();
    ScorePropertiesSettingsPage *m_scoreSettingsPage;
};

ScorePropertiesSettingsPageTest::ScorePropertiesSettingsPageTest()
    : m_scoreSettingsPage(0)
{
}

void ScorePropertiesSettingsPageTest::init()
{
    clearSettings();
    m_scoreSettingsPage = new ScorePropertiesSettingsPage();
}

void ScorePropertiesSettingsPageTest::cleanup()
{
    delete m_scoreSettingsPage;
}

void ScorePropertiesSettingsPageTest::testSetScoreArea()
{
    Score::Area testArea = Header;
    QVERIFY2(m_scoreSettingsPage->scoreArea() == NoArea,
             "Wrong default area");

    m_scoreSettingsPage->setScoreArea(testArea);

    QVERIFY2(m_scoreSettingsPage->scoreArea() == testArea,
             "Failed setting score area");
}

void ScorePropertiesSettingsPageTest::testPropertyWidgetDefaultValuesFromSettings()
{
    Score::Area testArea = Header;
    m_scoreSettingsPage->setScoreArea(testArea);

    testPropertiesWidget(testArea, LP::ScoreTitle);
    testPropertiesWidget(testArea, LP::ScoreType);
    testPropertiesWidget(testArea, LP::ScoreComposer);
    testPropertiesWidget(testArea, LP::ScoreArranger);
    testPropertiesWidget(testArea, LP::ScoreCopyright);
    testPropertiesWidget(testArea, LP::ScoreYear);
}

void ScorePropertiesSettingsPageTest::testPropertyWidgetValuesFromSettings()
{
    Score::Area testArea = Header;

    // Add some new settings
    ScoreSettings *settings = new ScoreSettings;
    settings->setScoreArea(testArea);
    settings->setDataRole(LP::ScoreTitle);
    settings->setValue(Row, 2);
    settings->setValue(Enabled, false);
    settings->setValue(Font, QFont("Times", 65, QFont::Light));
    settings->setValue(Color, QColor("#548736"));
    settings->setValue(Alignment, QVariant::fromValue<TextAlignment>(TextAlignment::Right));
    delete settings; // Force sync

    m_scoreSettingsPage->setScoreArea(testArea);

    testPropertiesWidget(testArea, LP::ScoreTitle);
}

void ScorePropertiesSettingsPageTest::testPropertiesWidget(Settings::Score::Area area, LP::ScoreDataRole testDataRole)
{
    ScoreSettings settings;
    settings.setScoreArea(area);
    settings.setDataRole(testDataRole);

    ScorePropertiesWidget *propertiesWidget = m_scoreSettingsPage->m_propertiesWidgets.value(testDataRole);
    Q_ASSERT(propertiesWidget);

    QVERIFY2(propertiesWidget->isWidgetEnabled() == settings.value(Enabled).toBool(),
             "Enabled state isn' set correct from settings");
    QVERIFY2(propertiesWidget->alignment() == settings.value(Alignment).value<TextAlignment>(),
             "Text alignment wasn't set correctly from settings");
    QVERIFY2(propertiesWidget->font() == settings.value(Font).value<QFont>(),
             "Font wasn't set correctly from settings");
    QVERIFY2(propertiesWidget->color() == settings.value(Color).value<QColor>(),
             "Color wasn't set correctly from settings");
    QVERIFY2(propertiesWidget->row() == settings.value(Row).toInt(),
             "Row wasn't set correctly from settings");
}

void ScorePropertiesSettingsPageTest::clearSettings()
{
    ScoreSettings settings;
    settings.clear();
    settings.sync();
}

QTEST_MAIN(ScorePropertiesSettingsPageTest)

#include "tst_scorepropertiessettingspagetest.moc"
