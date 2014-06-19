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
    qRegisterMetaType<QPageLayout::Unit>("QPageLayout::Unit");

    ui->setupUi(this);
    m_layoutSettings = new LayoutSettings(this);

    initPageFormatComboBox();
    initLayoutUnitComboBox();
    m_pageLayout = m_layoutSettings->pageLayout();
    initUi();
    createConnections();
}

void LayoutSettingsPage::createConnections()
{
    connect(ui->layoutUnitComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(currentLayoutUnitChanged(int)));
    connect(ui->paperFormatComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(currentPageSizeChanged(int)));
    connect(ui->topMarginSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(marginsChanged()));
    connect(ui->rightMarginSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(marginsChanged()));
    connect(ui->bottomMarginSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(marginsChanged()));
    connect(ui->leftMarginSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(marginsChanged()));
    connect(ui->portraitRadioButton, &QRadioButton::clicked,
            [this] {
        m_pageLayout.setOrientation(QPageLayout::Portrait);
        writePageLayoutSettings();
    });
    connect(ui->landscapeRadioButton, &QRadioButton::clicked,
            [this] {
        m_pageLayout.setOrientation(QPageLayout::Landscape);
        writePageLayoutSettings();
    });
    connect(ui->staffSpaceSpinBox, SIGNAL(valueChanged(double)),
            this, SLOT(staffSpaceChanged(double)));
}

LayoutSettingsPage::~LayoutSettingsPage()
{
    delete ui;
}

void LayoutSettingsPage::currentLayoutUnitChanged(int index)
{
    QVariant unitData = ui->layoutUnitComboBox->currentData();
    m_pageLayout.setUnits(unitData.value<QPageLayout::Unit>());
    writePageLayoutSettings();
    setUiFromPageLayout();
}

void LayoutSettingsPage::currentPageSizeChanged(int index)
{
    QVariant sizeData = ui->paperFormatComboBox->currentData();
    QPageSize pageSize(sizeData.value<QPageSize::PageSizeId>());
    m_pageLayout.setPageSize(pageSize);
    writePageLayoutSettings();
    setUiFromPageLayout();
}

void LayoutSettingsPage::writePageLayoutSettings()
{
    m_layoutSettings->setPageLayout(m_pageLayout);
}

void LayoutSettingsPage::marginsChanged()
{
    QMarginsF margins;
    margins.setTop(ui->topMarginSpinBox->value());
    margins.setRight(ui->rightMarginSpinBox->value());
    margins.setBottom(ui->bottomMarginSpinBox->value());
    margins.setLeft(ui->leftMarginSpinBox->value());

    m_pageLayout.setMargins(margins);
    writePageLayoutSettings();
}

void LayoutSettingsPage::restoreDefaultPageSize()
{
    m_pageLayout = m_layoutSettings->defaultPageLayout();
    setUiFromPageLayout();
    writePageLayoutSettings();
}

void LayoutSettingsPage::staffSpaceChanged(double spaceInMM)
{
    m_layoutSettings->setStaffSpaceMM(spaceInMM);
}

void LayoutSettingsPage::initPageFormatComboBox()
{
    foreach (QPageSize::PageSizeId sizeId, s_pageSizes) {
        QString sizeName = QPageSize::name(sizeId);
        ui->paperFormatComboBox->addItem(sizeName,
                                         QVariant::fromValue<QPageSize::PageSizeId>(sizeId));
    }
}

void LayoutSettingsPage::initLayoutUnitComboBox()
{
    QVector<QPageLayout::Unit> pageSizeUnits({QPageLayout::Millimeter,
                                         QPageLayout::Point,
                                         QPageLayout::Inch,
                                         QPageLayout::Pica,
                                         QPageLayout::Didot,
                                         QPageLayout::Cicero});
    foreach (const QPageLayout::Unit unit, pageSizeUnits) {
        ui->layoutUnitComboBox->addItem(LayoutSettings::pageLayoutUnitToString(unit),
                                        QVariant::fromValue<QPageLayout::Unit>(unit));
    }
}

void LayoutSettingsPage::setMarginSpinboxSuffixes(QString unitName)
{
    ui->leftMarginSpinBox->setSuffix(unitName);
    ui->bottomMarginSpinBox->setSuffix(unitName);
    ui->topMarginSpinBox->setSuffix(unitName);
    ui->rightMarginSpinBox->setSuffix(unitName);
}

void LayoutSettingsPage::setUiFromPageLayout()
{
    QPageSize::PageSizeId pageSize = m_pageLayout.pageSize().id();
    QVariant pageSizeData = QVariant::fromValue<QPageSize::PageSizeId>(pageSize);
    int pageSizeIndex = ui->paperFormatComboBox->findData(pageSizeData);
    ui->paperFormatComboBox->setCurrentIndex(pageSizeIndex);

    if (m_pageLayout.orientation() == QPageLayout::Portrait)
        ui->portraitRadioButton->setChecked(true);
    else
        ui->landscapeRadioButton->setChecked(true);

    QPageLayout::Unit unit = m_pageLayout.units();
    QVariant pageUnitData = QVariant::fromValue<QPageLayout::Unit>(unit);
    int pageUnitIndex = ui->layoutUnitComboBox->findData(pageUnitData);
    ui->layoutUnitComboBox->setCurrentIndex(pageUnitIndex);
    QString unitName = LayoutSettings::pageLayoutUnitToString(unit);

    QMarginsF margins = m_pageLayout.margins();
    ui->topMarginSpinBox->setValue(margins.top());
    ui->rightMarginSpinBox->setValue(margins.right());
    ui->bottomMarginSpinBox->setValue(margins.bottom());
    ui->leftMarginSpinBox->setValue(margins.left());
    setMarginSpinboxSuffixes(unitName);
}

void LayoutSettingsPage::initUi()
{
    setUiFromPageLayout();
    ui->staffSpaceSpinBox->setValue(m_layoutSettings->staffSpaceMM());
}
