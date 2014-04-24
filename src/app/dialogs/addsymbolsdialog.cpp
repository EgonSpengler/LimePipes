/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "addsymbolsdialog.h"
#include "ui_addsymbolsdialog.h"
#include <QListWidgetItem>

AddSymbolsDialog::AddSymbolsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSymbolsDialog)
{
    ui->setupUi(this);
    connect(ui->insertButton, SIGNAL(clicked()),
            this, SLOT(insertSymbolClicked()));
}

AddSymbolsDialog::~AddSymbolsDialog()
{
    delete ui;
}

void AddSymbolsDialog::clearSymbolList()
{
    ui->symbolsListWidget->clear();
}

void AddSymbolsDialog::addSymbol(const QString &name, int id)
{
    QListWidgetItem *newItem = new QListWidgetItem(name);
    newItem->setData(Qt::UserRole, id);
    ui->symbolsListWidget->addItem(newItem);
}

void AddSymbolsDialog::setSymbolNames(const QStringList &symbolNames)
{
    ui->symbolsListWidget->clear();
    ui->symbolsListWidget->addItems(symbolNames);
}

void AddSymbolsDialog::insertSymbolClicked()
{
    QListWidgetItem *currentItem = ui->symbolsListWidget->currentItem();
    if (currentItem) {
        int symbolType = currentItem->data(Qt::UserRole).toInt();
        emit insertSymbol(symbolType);
    }
}
