/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/layoutsettings.h>

#include "layoutsettingspage.h"
#include "ui_layoutsettingspage.h"

LayoutSettingsPage::LayoutSettingsPage(QWidget *parent)
    : QFrame(parent),
      ui(new Ui::LayoutSettingsPage)
{
    ui->setupUi(this);

    m_layoutSettings = new LayoutSettings(this);
}

LayoutSettingsPage::~LayoutSettingsPage()
{
    delete ui;
}
