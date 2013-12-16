/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QSpinBox>
#include <QFontDialog>
#include <QColorDialog>
#include "scorepropertieswidget.h"
#include "ui_scorepropertieswidget.h"

ScorePropertiesWidget::ScorePropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScorePropertiesWidget)
{
    ui->setupUi(this);

    QVariant value;
    value.setValue(Settings::TextAlignment::Left);
    ui->alignmentComboBox->addItem(tr("Left"), value);
    value.setValue(Settings::TextAlignment::Center);
    ui->alignmentComboBox->addItem(tr("Center"), value);
    value.setValue(Settings::TextAlignment::Right);
    ui->alignmentComboBox->addItem(tr("Right"), value);

    createConnections();

    setWidgetEnabled(ui->enabledCheckBox->isChecked());
}

void ScorePropertiesWidget::createConnections()
{
    connect(ui->enabledCheckBox, &QCheckBox::toggled,
            this, &ScorePropertiesWidget::setWidgetEnabled);
    connect(ui->fontPushButton, &QPushButton::clicked,
            this, &ScorePropertiesWidget::fontChangeClicked);
    connect(ui->colorPushButton, &QPushButton::clicked,
            this, &ScorePropertiesWidget::colorChangeClicked);
    connect(ui->rowSpinBox, SIGNAL(valueChanged(int)),
            this, SIGNAL(rowChanged(int)));
    connect(ui->alignmentComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(newAlignmentSelected(int)));
}

ScorePropertiesWidget::~ScorePropertiesWidget()
{
    delete ui;
}

void ScorePropertiesWidget::setText(const QString &text)
{
    ui->textLabel->setText(text);
}

void ScorePropertiesWidget::setAlignment(Settings::TextAlignment alignment)
{
    QVariant value = QVariant::fromValue<Settings::TextAlignment>(alignment);
    int alignmentIndex = ui->alignmentComboBox->findData(value);
    if (alignmentIndex == -1)
        return;

    ui->alignmentComboBox->setCurrentIndex(alignmentIndex);
}

Settings::TextAlignment ScorePropertiesWidget::alignment() const
{
    return ui->alignmentComboBox->currentData().value<Settings::TextAlignment>();
}

void ScorePropertiesWidget::setRow(int row)
{
    if (row < ui->rowSpinBox->minimum())
        row = ui->rowSpinBox->minimum();
    if (row > ui->rowSpinBox->maximum())
        row = ui->rowSpinBox->maximum();

    ui->rowSpinBox->setValue(row);
}

int ScorePropertiesWidget::row() const
{
    return ui->rowSpinBox->value();
}

void ScorePropertiesWidget::setFont(const QFont &font)
{
    ui->textLabel->setFont(font);
}

QFont ScorePropertiesWidget::font() const
{
    return ui->textLabel->font();
}

void ScorePropertiesWidget::setColor(const QColor &color)
{
    QPalette palette(ui->textLabel->palette());
    palette.setBrush(QPalette::Foreground, color);
    ui->textLabel->setPalette(palette);
}

QColor ScorePropertiesWidget::color() const
{
    QPalette palette(ui->textLabel->palette());
    return palette.brush(QPalette::Foreground).color();
}

bool ScorePropertiesWidget::isWidgetEnabled() const
{
    return ui->enabledCheckBox->isChecked();
}

void ScorePropertiesWidget::setWidgetEnabled(bool enabled)
{
    ui->textLabel->setEnabled(enabled);
    ui->rowLabel->setEnabled(enabled);
    ui->rowSpinBox->setEnabled(enabled);
    ui->alignmentLabel->setEnabled(enabled);
    ui->alignmentComboBox->setEnabled(enabled);
    ui->fontPushButton->setEnabled(enabled);
    ui->colorPushButton->setEnabled(enabled);
}

void ScorePropertiesWidget::fontChangeClicked()
{
    QFont currentFont(font());
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, currentFont, this);
    if (ok) {
        if (newFont != currentFont) {
            setFont(newFont);
            emit fontChanged(newFont);
        }
    }
}

void ScorePropertiesWidget::colorChangeClicked()
{
    QColor currentColor(color());
    QColor newColor = QColorDialog::getColor(currentColor, this);
    if (!newColor.isValid())
        return;

    if (newColor != currentColor) {
        setColor(newColor);
        emit colorChanged(newColor);
    }
}

void ScorePropertiesWidget::newAlignmentSelected(int index)
{
    Settings::TextAlignment alignment;
    alignment = ui->alignmentComboBox->currentData().value<Settings::TextAlignment>();

    emit alignmentChanged(alignment);
}
