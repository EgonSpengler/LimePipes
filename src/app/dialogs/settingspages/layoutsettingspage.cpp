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
    m_layoutSettings = new LayoutSettings(this);

    initPageFormatComboBox();
    initUiWithSettings();
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

void LayoutSettingsPage::initUiWithSettings()
{
    QPageLayout pageLayout = m_layoutSettings->pageLayout();

    QPageSize::PageSizeId pageSize = pageLayout.pageSize().id();
    QVariant pageSizeData = QVariant::fromValue<QPageSize::PageSizeId>(pageSize);
    int pageSizeIndex = ui->paperFormatComboBox->findData(pageSizeData);
    ui->paperFormatComboBox->setCurrentIndex(pageSizeIndex);

    if (pageLayout.orientation() == QPageLayout::Portrait)
        ui->portraitRadioButton->setChecked(true);
    else
        ui->landscapeRadioButton->setChecked(true);

    QPageLayout::Unit unit = pageLayout.units();
    QString unitName = pageLayoutUnitToString(unit);

    QMarginsF margins = pageLayout.margins();
    ui->topMarginSpinBox->setValue(margins.top());
    ui->topMarginSpinBox->setSuffix(unitName);
    ui->rightMarginSpinBox->setValue(margins.right());
    ui->rightMarginSpinBox->setSuffix(unitName);
    ui->bottomMarginSpinBox->setValue(margins.bottom());
    ui->bottomMarginSpinBox->setSuffix(unitName);
    ui->leftMarginSpinBox->setValue(margins.left());
    ui->leftMarginSpinBox->setSuffix(unitName);
}

QString LayoutSettingsPage::pageLayoutUnitToString(const QPageLayout::Unit &unit)
{
    switch (unit) {
    case QPageLayout::Millimeter:
        return tr("mm");
    case QPageLayout::Point:
        return tr("pt");
    case QPageLayout::Inch:
        return tr("in");
    case QPageLayout::Pica:
        return tr("pica");
    case QPageLayout::Didot:
        return tr("didot");
    case QPageLayout::Cicero:
        return tr("cicero");
    default:
        return QStringLiteral("");
    }
}
