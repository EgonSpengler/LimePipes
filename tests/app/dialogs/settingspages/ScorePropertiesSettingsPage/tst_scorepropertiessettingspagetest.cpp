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
    void testCheckAllPropertyWidgetPositions();
    void testPropertyWidgetEnabledChanged();
    void testPropertyWidgetColorChanged();
    void testPropertyWidgetFontChanged();

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

void ScorePropertiesSettingsPageTest::testCheckAllPropertyWidgetPositions()
{
    Score::Area testArea = Header;
    int scoreTitleRow = 1;
    int scoreComposerRow = 1;
    Settings::TextAlignment scoreTitleAlignment = Settings::TextAlignment::Left;
    Settings::TextAlignment scoreComposerAlignment = Settings::TextAlignment::Right;
    m_scoreSettingsPage->setScoreArea(testArea);
    ScoreSettings settings;
    settings.setScoreArea(testArea);

    // Set title and composer enabled and to different positions
    for (auto it = m_scoreSettingsPage->m_propertiesWidgets.constBegin();
         it != m_scoreSettingsPage->m_propertiesWidgets.constEnd(); it++) {
        if (it.key() == LP::ScoreTitle) {
            it.value()->setWidgetEnabled(true);
            it.value()->setRow(scoreTitleRow);
            it.value()->setAlignment(scoreTitleAlignment);
        } else if (it.key() == LP::ScoreComposer) {
            it.value()->setWidgetEnabled(true);
            it.value()->setRow(scoreComposerRow);
            it.value()->setAlignment(scoreComposerAlignment);
        } else {
            it.value()->setWidgetEnabled(false);
        }
    }

    m_scoreSettingsPage->checkAllPropertyWidgetPositionValues();

    // After check, no property widget must have the position in use message active
    for (auto it = m_scoreSettingsPage->m_propertiesWidgets.constBegin();
         it != m_scoreSettingsPage->m_propertiesWidgets.constEnd(); it++) {
        QVERIFY2(it.value()->isPositionInUseMessageActive() == false,
                 "At least one position in use message is set active");
    }

    // Settings must have correct values for Row and Alignment
    settings.setDataRole(LP::ScoreTitle);
    QVERIFY2(settings.value(Row).toInt() == scoreTitleRow,
             "Title row wasn't stored in settings");
    QVERIFY2(settings.value(Alignment).value<TextAlignment>() == scoreTitleAlignment,
             "Alignment wasn't stored in settings");
    settings.setDataRole(LP::ScoreComposer);
    QVERIFY2(settings.value(Row).toInt() == scoreComposerRow,
             "Composer row wasn't stored in settings");
    QVERIFY2(settings.value(Alignment).value<TextAlignment>() == scoreComposerAlignment,
             "Alignment wasn't stored in settings");

    // Set one Score title position to composer position
    ScorePropertiesWidget *titlePropertiesWidget =
            m_scoreSettingsPage->m_propertiesWidgets.value(LP::ScoreTitle);
    Q_ASSERT(titlePropertiesWidget);
    titlePropertiesWidget->setRow(scoreComposerRow);
    titlePropertiesWidget->setAlignment(scoreComposerAlignment);

    m_scoreSettingsPage->checkAllPropertyWidgetPositionValues();

    // Now after check, title and composer widgets must have position in use message active
    for (auto it = m_scoreSettingsPage->m_propertiesWidgets.constBegin();
         it != m_scoreSettingsPage->m_propertiesWidgets.constEnd(); it++) {
        if (it.key() == LP::ScoreTitle || it.key() == LP::ScoreComposer) {
            QVERIFY2(it.value()->isPositionInUseMessageActive() == true,
                    "Title and composer widgets must have position in use message set active");
        } else {
            QVERIFY2(it.value()->isPositionInUseMessageActive() == false,
                     "Non title and composer widget has position in use message active");
        }
    }

    // Settings must be the same as before, because title has now the same position as composer
    settings.setDataRole(LP::ScoreTitle);
    QVERIFY2(settings.value(Row).toInt() == scoreTitleRow,
             "Title row wasn't stored in settings");
    QVERIFY2(settings.value(Alignment).value<TextAlignment>() == scoreTitleAlignment,
             "Alignment wasn't stored in settings");
    settings.setDataRole(LP::ScoreComposer);
    QVERIFY2(settings.value(Row).toInt() == scoreComposerRow,
             "Composer row wasn't stored in settings");
    QVERIFY2(settings.value(Alignment).value<TextAlignment>() == scoreComposerAlignment,
             "Alignment wasn't stored in settings");
}

void ScorePropertiesSettingsPageTest::testPropertyWidgetEnabledChanged()
{
    Score::Area testArea = Header;
    m_scoreSettingsPage->setScoreArea(testArea);
    LP::ScoreDataRole testDataRole = LP::ScoreTitle;
    ScoreSettings settings;
    settings.setScoreArea(testArea);
    settings.setDataRole(testDataRole);
    ScorePropertiesWidget *testWidget = m_scoreSettingsPage->m_propertiesWidgets.value(testDataRole);
    Q_ASSERT(testWidget);

    testWidget->setWidgetEnabled(true);
    m_scoreSettingsPage->propertyWidgetEnabledChanged(testWidget);
    QVERIFY2(settings.value(Enabled).toBool() == true,
             "Enabled state wasn't stored in settings");

    testWidget->setWidgetEnabled(false);
    m_scoreSettingsPage->propertyWidgetEnabledChanged(testWidget);
    QVERIFY2(settings.value(Enabled).toBool() == false,
             "Enabled state wasn't stored in settings");
}

void ScorePropertiesSettingsPageTest::testPropertyWidgetColorChanged()
{
    Score::Area testArea = Header;
    QColor testColor("#234564");
    m_scoreSettingsPage->setScoreArea(testArea);
    LP::ScoreDataRole testDataRole = LP::ScoreTitle;
    ScoreSettings settings;
    settings.setScoreArea(testArea);
    settings.setDataRole(testDataRole);
    ScorePropertiesWidget *testWidget = m_scoreSettingsPage->m_propertiesWidgets.value(testDataRole);
    Q_ASSERT(testWidget);

    testWidget->setColor(testColor);
    m_scoreSettingsPage->propertyWidgetColorChanged(testWidget);
    QVERIFY2(settings.value(Color).value<QColor>() == testColor,
             "Color wasn't stored in settings");
}

void ScorePropertiesSettingsPageTest::testPropertyWidgetFontChanged()
{
    Score::Area testArea = Header;
    QFont testFont("Arial", 54, QFont::Light);
    m_scoreSettingsPage->setScoreArea(testArea);
    LP::ScoreDataRole testDataRole = LP::ScoreTitle;
    ScoreSettings settings;
    settings.setScoreArea(testArea);
    settings.setDataRole(testDataRole);
    ScorePropertiesWidget *testWidget = m_scoreSettingsPage->m_propertiesWidgets.value(testDataRole);
    Q_ASSERT(testWidget);

    testWidget->setFont(testFont);
    m_scoreSettingsPage->propertyWidgetFontChanged(testWidget);
    QVERIFY2(settings.value(Font).value<QFont>() == testFont,
             "Font wasn't stored in settings");
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
