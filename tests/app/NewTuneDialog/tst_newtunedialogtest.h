/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef NEWTUNEDIALOGTEST_H
#define NEWTUNEDIALOGTEST_H

#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QDialogButtonBox>

#include <QObject>
#include <app/newtunedialog.h>

class NewTuneDialogTest : public QObject
{
    Q_OBJECT
    
public:
    NewTuneDialogTest()
        : m_dialog(0), m_instrumentsCombo(0), m_buttonBox(0), m_okButton(0), m_titleLineEdit(0) {}
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testInstrumentsComboFilled();
    void testEnableDisableOkButton();

private:
    NewTuneDialog *m_dialog;
    QComboBox *m_instrumentsCombo;
    QDialogButtonBox *m_buttonBox;
    QPushButton *m_okButton;
    QLineEdit *m_titleLineEdit;
};

#endif
