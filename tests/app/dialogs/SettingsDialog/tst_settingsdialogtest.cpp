/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <app/dialogs/settingsdialog.h>

class SettingsDialogTest : public QObject
{
    Q_OBJECT

public:
    SettingsDialogTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testCase1();

private:
    SettingsDialog *m_settingsDialog;
};

SettingsDialogTest::SettingsDialogTest()
    : m_settingsDialog(0)
{
}

void SettingsDialogTest::init()
{
    m_settingsDialog = new SettingsDialog();
}

void SettingsDialogTest::cleanup()
{
    delete m_settingsDialog;
}

void SettingsDialogTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(SettingsDialogTest)

#include "tst_settingsdialogtest.moc"
