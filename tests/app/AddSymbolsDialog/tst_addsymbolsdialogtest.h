/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ADDSYMBOLSDIALOGTEST_H
#define ADDSYMBOLSDIALOGTEST_H

#include <QObject>
#include <QListWidget>
#include <app/addsymbolsdialog.h>

class AddSymbolsDialogTest : public QObject
{
    Q_OBJECT
    
public:
    AddSymbolsDialogTest()
        : m_dialog(0), m_symbolsListWidget(0), m_insertButton(0) {}
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testSetSymbolNames();
    void testInsertSymbol();

private:
    AddSymbolsDialog *m_dialog;
    QListWidget *m_symbolsListWidget;
    QPushButton *m_insertButton;
};

#endif
