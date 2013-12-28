/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <app/dialogs/settingspages/scorepropertieswidget.h>

class ScorePropertiesWidgetTest : public QObject
{
    Q_OBJECT

public:
    ScorePropertiesWidgetTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testCase1();

private:
    ScorePropertiesWidget *m_scorePropertiesWidget;
};

ScorePropertiesWidgetTest::ScorePropertiesWidgetTest()
    : m_scorePropertiesWidget(0)
{
}

void ScorePropertiesWidgetTest::init()
{
    m_scorePropertiesWidget = new ScorePropertiesWidget();
}

void ScorePropertiesWidgetTest::cleanup()
{
    delete m_scorePropertiesWidget;
}

void ScorePropertiesWidgetTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(ScorePropertiesWidgetTest)

#include "tst_scorepropertieswidgettest.moc"
