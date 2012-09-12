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

#include "../../../src/app/addsymbolsdialog.h"

class AddSymbolsDialogTest : public QObject
{
    Q_OBJECT
    
public:
    AddSymbolsDialogTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();

private:
    AddSymbolsDialog *m_dialog;
};

AddSymbolsDialogTest::AddSymbolsDialogTest()
{
}

void AddSymbolsDialogTest::initTestCase()
{
    m_dialog = new AddSymbolsDialog();
}

void AddSymbolsDialogTest::cleanupTestCase()
{
    delete m_dialog;
}

void AddSymbolsDialogTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_MAIN(AddSymbolsDialogTest)

#include "tst_addsymbolsdialogtest.moc"
