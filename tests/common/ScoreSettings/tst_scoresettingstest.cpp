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

class ScoreSettingsTest : public QObject
{
    Q_OBJECT

public:
    ScoreSettingsTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testCase1();

private:
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

void ScoreSettingsTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ScoreSettingsTest)

#include "tst_scoresettingstest.moc"
