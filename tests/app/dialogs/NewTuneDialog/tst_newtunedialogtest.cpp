/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include "tst_newtunedialogtest.h"

void NewTuneDialogTest::initTestCase()
{
    m_dialog = new NewTuneDialog( QStringList() << "First instrument" << "Second instrument");

    m_instrumentsCombo = m_dialog->findChild<QComboBox*>("instrumentsComboBox");
    Q_ASSERT(m_instrumentsCombo);

    m_buttonBox = m_dialog->findChild<QDialogButtonBox*>("buttonBox");
    Q_ASSERT(m_buttonBox);

    m_okButton = m_buttonBox->button(QDialogButtonBox::Ok);
    Q_ASSERT(m_okButton);

    m_titleLineEdit = m_dialog->findChild<QLineEdit*>("titleLineEdit");
    Q_ASSERT(m_titleLineEdit);
}

void NewTuneDialogTest::cleanupTestCase()
{
    delete m_dialog;
}

void NewTuneDialogTest::testInstrumentsComboFilled()
{
    QVERIFY2(m_instrumentsCombo->count() == 2, "Failure, instrumentnames were not set in constructor");
}

void NewTuneDialogTest::testEnableDisableOkButton()
{
    m_titleLineEdit->clear();
    QVERIFY2(m_okButton->isEnabled() == false,
             "Failed, with no Title for the score, the ok button should be disabled");

    // With only whitespace, the ok button should still be disabled
    QTest::keyClicks(m_titleLineEdit, "   ");
    QVERIFY2(m_okButton->isEnabled() == false,
             "Failed. If title consists only of whitespace, the button should still be disabled");

    // With text, the button should be enabled
    QString testText = "hello";
    m_titleLineEdit->clear();

    QTest::keyClicks(m_titleLineEdit, testText);
    QVERIFY2(m_okButton->isEnabled() == true,
             "Failed. Ok button should be enabled if filled with text");

    for (int i = 0; i < testText.length(); i++) {
        QTest::keyClick(m_titleLineEdit, Qt::Key_Backspace);
    }
    QVERIFY2(m_okButton->isEnabled() == false, "Ok button should be disabled after deleting all Text from title line edit");
}

QTEST_MAIN(NewTuneDialogTest)
