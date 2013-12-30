/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QSettings>
#include <QFont>
#include <common/scoresettings.h>

using namespace Settings;
using namespace Settings::Score;

class ScoreSettingsTest : public QObject
{
    Q_OBJECT

public:
    ScoreSettingsTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testSetGetScoreArea();
    void testSetGetDataRole();
    void testDefaultValues();
    void testSetEnabled();
    void testSetFont();
    void testSetColor();
    void testSetRow();
    void testSetAlignment();

private:
    void clearSettings();
    ScoreSettings *m_scoreSettings;
};

ScoreSettingsTest::ScoreSettingsTest()
    : m_scoreSettings(0)
{
}

void ScoreSettingsTest::init()
{
    m_scoreSettings = new ScoreSettings(this);
}

void ScoreSettingsTest::cleanup()
{
    clearSettings();
    delete m_scoreSettings;
}

void ScoreSettingsTest::testSetGetScoreArea()
{
    m_scoreSettings->setScoreArea(Header);
    QVERIFY2(m_scoreSettings->scoreArea() == Header,
             "Can't set and get score area");
}

void ScoreSettingsTest::testSetGetDataRole()
{
    LP::ScoreDataRole testDataRole = LP::ScoreComposer;
    m_scoreSettings->setDataRole(testDataRole);
    QVERIFY2(m_scoreSettings->dataRole() == testDataRole,
             "Can't set and get data role");
}

void ScoreSettingsTest::testDefaultValues()
{
    clearSettings();

    // Header
    m_scoreSettings->setScoreArea(Header);

    // Title
    m_scoreSettings->setDataRole(LP::ScoreTitle);
    QFont titleFont("Arial", 18, QFont::Bold);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == true,
            "Setting is not enabled");
    QVERIFY2(m_scoreSettings->value(Row).toInt() == 1,
            "Setting is not in correct row");
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == TextAlignment::Center,
            "Setting has not correct alignment");
    QVERIFY2(m_scoreSettings->value(Font).value<QFont>() == titleFont,
            "Setting has not correct font");

    // Type
    m_scoreSettings->setDataRole(LP::ScoreType);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == true,
            "Setting is not enabled");
    QVERIFY2(m_scoreSettings->value(Row).toInt() == 1,
            "Setting is not in correct row");
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == TextAlignment::Left,
            "Setting has not correct alignment");

    // Composer
    m_scoreSettings->setDataRole(LP::ScoreComposer);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == true,
            "Setting is not enabled");
    QVERIFY2(m_scoreSettings->value(Row).toInt() == 1,
            "Setting is not in correct row");
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == TextAlignment::Right,
            "Setting has not correct alignment");

    // Arranger
    m_scoreSettings->setDataRole(LP::ScoreArranger);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == true,
            "Setting is not enabled");
    QVERIFY2(m_scoreSettings->value(Row).toInt() == 2,
            "Setting is not in correct row");
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == TextAlignment::Right,
            "Setting has not correct alignment");

    // Footer
    m_scoreSettings->setScoreArea(Footer);

    // Year
    m_scoreSettings->setDataRole(LP::ScoreYear);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == true,
            "Setting is not enabled");
    QVERIFY2(m_scoreSettings->value(Row).toInt() == 1,
            "Setting is not in correct row");
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == TextAlignment::Left,
            "Setting has not correct alignment");

    // Copyright
    m_scoreSettings->setDataRole(LP::ScoreCopyright);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == true,
            "Setting is not enabled");
    QVERIFY2(m_scoreSettings->value(Row).toInt() == 1,
            "Setting is not in correct row");
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == TextAlignment::Right,
             "Setting has not correct alignment");
}

void ScoreSettingsTest::testSetEnabled()
{
    clearSettings();

    m_scoreSettings->setScoreArea(Header);
    m_scoreSettings->setDataRole(LP::ScoreTitle);

    bool enabledByDefault = m_scoreSettings->value(Enabled).toBool();
    m_scoreSettings->setValue(Enabled, !enabledByDefault);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == !enabledByDefault,
             "Enabled state of setting couldn't be toggled");
}

void ScoreSettingsTest::testSetFont()
{
    QFont testFont("Times", 56, QFont::DemiBold);
    clearSettings();

    m_scoreSettings->setScoreArea(Header);
    m_scoreSettings->setDataRole(LP::ScoreTitle);
    QVERIFY2(m_scoreSettings->value(Font).value<QFont>() != testFont,
             "Default font is testfont");
    m_scoreSettings->setValue(Font, QVariant::fromValue<QFont>(testFont));
    QVERIFY2(m_scoreSettings->value(Font).value<QFont>() == testFont,
             "Font can't be set and get back from setting");
}

void ScoreSettingsTest::testSetColor()
{
    QColor testColor("#459207");
    clearSettings();

    m_scoreSettings->setScoreArea(Header);
    m_scoreSettings->setDataRole(LP::ScoreTitle);
    QVERIFY2(m_scoreSettings->value(Color).value<QColor>() != testColor,
             "Default color is testColor");
    m_scoreSettings->setValue(Color, QVariant::fromValue<QColor>(testColor));
    QVERIFY2(m_scoreSettings->value(Color).value<QColor>() == testColor,
             "Can't get color from settings");

}

void ScoreSettingsTest::testSetRow()
{
    int testRow = 12;
    clearSettings();

    m_scoreSettings->setScoreArea(Header);
    m_scoreSettings->setDataRole(LP::ScoreTitle);
    QVERIFY2(m_scoreSettings->value(Row).toInt() != testRow,
             "Default row is testRow");
    m_scoreSettings->setValue(Row, testRow);
    QVERIFY2(m_scoreSettings->value(Row).toInt() == testRow,
             "Can't get row from settings");

}

void ScoreSettingsTest::testSetAlignment()
{
    TextAlignment testAlignment = TextAlignment::Center;
    TextAlignment alternativeAlignment = TextAlignment::Left;
    clearSettings();

    m_scoreSettings->setScoreArea(Header);
    m_scoreSettings->setDataRole(LP::ScoreTitle);
    TextAlignment currentAlignment = m_scoreSettings->value(Alignment).value<TextAlignment>();
    if (currentAlignment == testAlignment) {
        testAlignment = alternativeAlignment;
    }
    m_scoreSettings->setValue(Alignment, QVariant::fromValue<TextAlignment>(testAlignment));
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == testAlignment,
             "Can't get alignment from settings");

}

void ScoreSettingsTest::clearSettings()
{
    m_scoreSettings->m_settings->clear();
    m_scoreSettings->m_settings->sync();
}

QTEST_APPLESS_MAIN(ScoreSettingsTest)

#include "tst_scoresettingstest.moc"
