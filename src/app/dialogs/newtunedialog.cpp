/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "newtunedialog.h"
#include "ui_newtunedialog.h"
#include <QPushButton>

NewTuneDialog::NewTuneDialog(const QList<QString> &instruments, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTuneDialog)
{
    ui->setupUi(this);
    ui->instrumentsComboBox->addItems(instruments);
    setOkButtonEnabled(false);
    createConnections();
    ui->titleLineEdit->setFocus();
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

void NewTuneDialog::createConnections()
{
    connect(ui->titleLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(textChanged(QString)));
}

void NewTuneDialog::textChanged(const QString &text)
{
    bool okButtonEnabled = text.trimmed().isEmpty() ? false : true;
    setOkButtonEnabled(okButtonEnabled);
}

void NewTuneDialog::setOkButtonEnabled(bool enabled)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(enabled);
}
