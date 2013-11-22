/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>

class ScorePropertiesDialogTest : public QObject
{
    Q_OBJECT

public:
    ScorePropertiesDialogTest();

private Q_SLOTS:
    void testCase1();
};

ScorePropertiesDialogTest::ScorePropertiesDialogTest()
{
}

void ScorePropertiesDialogTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(ScorePropertiesDialogTest)

#include "tst_scorepropertiesdialogtest.moc"
