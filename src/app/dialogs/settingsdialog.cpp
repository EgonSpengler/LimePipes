/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QListWidgetItem>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <common/settingdefines.h>

using namespace Settings::Score;

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    ui->menuListWidget->setCurrentRow(0);

    ui->scoreHeaderTab->setScoreArea(Header);
    ui->scoreFooterTab->setScoreArea(Footer);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
