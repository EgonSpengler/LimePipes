/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPageLayout>

#include <common/layoutsettings.h>

#include "layoutsettingspage.h"
#include "ui_layoutsettingspage.h"

QVector<QPageSize::PageSizeId>
LayoutSettingsPage::s_pageSizes({QPageSize::A6,
                                 QPageSize::A5,
                                 QPageSize::A4,
                                 QPageSize::A3,
                                 QPageSize::B6,
                                 QPageSize::B5,
                                 QPageSize::B4,
                                 QPageSize::Letter,
                                 QPageSize::Legal,
                                 QPageSize::Tabloid
                                                               });

LayoutSettingsPage::LayoutSettingsPage(QWidget *parent)
    : QFrame(parent),
      ui(new Ui::LayoutSettingsPage)
{
    qRegisterMetaType<QPageSize::PageSizeId>("QPageSize::PageSizeId");
    ui->setupUi(this);

    initPageFormatComboBox();
    m_layoutSettings = new LayoutSettings(this);
}

LayoutSettingsPage::~LayoutSettingsPage()
{
    delete ui;
}

void LayoutSettingsPage::initPageFormatComboBox()
{
    foreach (QPageSize::PageSizeId sizeId, s_pageSizes) {
        QString sizeName = QPageSize::name(sizeId);
        ui->paperFormatComboBox->addItem(sizeName,
                                         QVariant::fromValue<QPageSize::PageSizeId>(sizeId));
    }
}
