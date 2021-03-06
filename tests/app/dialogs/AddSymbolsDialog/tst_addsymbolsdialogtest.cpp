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
#include <QListWidgetItem>
#include <QPushButton>
#include <QtTest/QSignalSpy>
#include "tst_addsymbolsdialogtest.h"

void AddSymbolsDialogTest::initTestCase()
{
    m_dialog = new AddSymbolsDialog();

    m_symbolsListWidget = m_dialog->findChild<QListWidget*>("symbolsListWidget");
    Q_ASSERT(m_symbolsListWidget);

    m_insertButton = m_dialog->findChild<QPushButton*>("insertButton");
    Q_ASSERT(m_insertButton);
}

void AddSymbolsDialogTest::cleanupTestCase()
{
    delete m_dialog;
}

void AddSymbolsDialogTest::testSetSymbolNames()
{
    m_symbolsListWidget->clear();
    m_dialog->setSymbolNames(QStringList() << "Symbol 1" << "Symbol 2");
    QVERIFY2(m_symbolsListWidget->count() == 2, "Failed setting symbol names");
}

void AddSymbolsDialogTest::testInsertSymbol()
{
    m_symbolsListWidget->clear();
    QSignalSpy spy(m_dialog, SIGNAL(insertSymbol(QString)));

    m_symbolsListWidget->insertItems(0, QStringList() << "Symbol 1" << "Symbol 2" << "Symbol 3");
    QListWidgetItem *item = m_symbolsListWidget->item(1);
    m_symbolsListWidget->setCurrentItem(item);

    QTest::mouseClick(m_insertButton, Qt::LeftButton);
    QVERIFY2(spy.count() == 1, "Signal for inserting symbol wasn't emitted");
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY2(arguments.at(0).toString() == "Symbol 2", "Failed getting correct symbol name from insert signal");

    delete item;
}

QTEST_MAIN(AddSymbolsDialogTest)
