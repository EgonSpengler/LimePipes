/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "addsymbolsdialog.h"
#include "ui_addsymbolsdialog.h"

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

void AddSymbolsDialog::setSymbolNames(const QStringList &symbolNames)
{
    ui->symbolsListWidget->clear();
    ui->symbolsListWidget->addItems(symbolNames);
}

void AddSymbolsDialog::insertSymbolClicked()
{
    QListWidgetItem *currentItem = ui->symbolsListWidget->currentItem();
    if (currentItem) {
        emit insertSymbol(currentItem->text());
    }
}
