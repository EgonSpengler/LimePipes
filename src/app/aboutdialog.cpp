/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <LimePipesConfig.h>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->labelLimePipesVersion->setText(Project_VERSION);
    ui->labelQtVersion->setText(QT_VERSION_STR);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
