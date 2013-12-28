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

    m_scoreSettings->setScoreArea(Header);

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

    m_scoreSettings->setDataRole(LP::ScoreType);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == true,
            "Setting is not enabled");
    QVERIFY2(m_scoreSettings->value(Row).toInt() == 1,
            "Setting is not in correct row");
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == TextAlignment::Left,
            "Setting has not correct alignment");

    m_scoreSettings->setDataRole(LP::ScoreComposer);
    QVERIFY2(m_scoreSettings->value(Enabled).toBool() == true,
            "Setting is not enabled");
    QVERIFY2(m_scoreSettings->value(Row).toInt() == 1,
            "Setting is not in correct row");
    QVERIFY2(m_scoreSettings->value(Alignment).value<TextAlignment>() == TextAlignment::Right,
            "Setting has not correct alignment");
}

void ScoreSettingsTest::clearSettings()
{
    m_scoreSettings->m_settings->clear();
    m_scoreSettings->m_settings->sync();
}

QTEST_APPLESS_MAIN(ScoreSettingsTest)

#include "tst_scoresettingstest.moc"
