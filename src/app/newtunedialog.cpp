/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "newtunedialog.h"
#include "ui_newtunedialog.h"

NewTuneDialog::NewTuneDialog(const QList<QString> &instruments, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTuneDialog)
{
    ui->setupUi(this);
    ui->instrumentsComboBox->addItems(instruments);
}

NewTuneDialog::~NewTuneDialog()
{
    delete ui;
}

QString NewTuneDialog::scoreTitle() const
{
    return ui->titleLineEdit->text();
}

QString NewTuneDialog::instrumentTitle() const
{
    return ui->instrumentsComboBox->currentText();
}
