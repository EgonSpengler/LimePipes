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

ScorePropertiesWidget::ScorePropertiesWidget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ScorePropertiesWidget),
      m_widgetIsEnabled(false),
      m_textAlignment(Settings::TextAlignment::NoAlignment),
      m_row(0)
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

    setPositionIsInUseMessage(false);
}

void ScorePropertiesWidget::createConnections()
{
    connect(ui->fontPushButton, &QPushButton::clicked,
            this, &ScorePropertiesWidget::fontChangeClicked);
    connect(ui->colorPushButton, &QPushButton::clicked,
            this, &ScorePropertiesWidget::colorChangeClicked);
    connect(ui->rowSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(newRowSelected(int)));
    connect(ui->alignmentComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(newAlignmentSelected(int)));
    connect(ui->enabledCheckBox, &QCheckBox::toggled,
            [this] {
        bool checkBoxIsChecked = ui->enabledCheckBox->isChecked();
        if (checkBoxIsChecked != m_widgetIsEnabled) {
            emit enabledChanged(checkBoxIsChecked);
            setWidgetEnabled(checkBoxIsChecked);
        }
    });
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
    if (m_textAlignment == alignment)
        return;
    m_textAlignment = alignment;

    QVariant value = QVariant::fromValue<Settings::TextAlignment>(alignment);
    int alignmentIndex = ui->alignmentComboBox->findData(value);
    if (alignmentIndex == -1)
        return;

    ui->alignmentComboBox->setCurrentIndex(alignmentIndex);
}

Settings::TextAlignment ScorePropertiesWidget::alignment() const
{
    return m_textAlignment;
}

void ScorePropertiesWidget::setRow(int row)
{
    if (m_row == row)
        return;

    m_row = row;

    ui->rowSpinBox->setValue(row);
}

int ScorePropertiesWidget::row() const
{
    return m_row;
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
    if (m_widgetIsEnabled == enabled)
        return;
    m_widgetIsEnabled = enabled;

    ui->enabledCheckBox->setChecked(enabled);
    ui->textLabel->setEnabled(enabled);
    ui->rowLabel->setEnabled(enabled);
    ui->rowSpinBox->setEnabled(enabled);
    ui->alignmentLabel->setEnabled(enabled);
    ui->alignmentComboBox->setEnabled(enabled);
    ui->fontPushButton->setEnabled(enabled);
    ui->colorPushButton->setEnabled(enabled);
    ui->positionIsInUseLabel->setEnabled(enabled);
}

void ScorePropertiesWidget::setPositionIsInUseMessage(bool on)
{
    QString message(tr("Position is already in use"));
    QString style;
    if (on) {
        style = "color: rgb(255, 11, 22);";
    } else {
        message.clear();
    }

    ui->rowLabel->setStyleSheet(style);
    ui->rowSpinBox->setStyleSheet(style);
    ui->alignmentLabel->setStyleSheet(style);
    ui->alignmentComboBox->setStyleSheet(style);
    ui->positionIsInUseLabel->setStyleSheet(style);

    ui->positionIsInUseLabel->setText(message);
}

bool ScorePropertiesWidget::isPositionInUseMessageActive() const
{
    return !(ui->positionIsInUseLabel->text().isEmpty());
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
    Q_UNUSED(index);

    Settings::TextAlignment alignment;
    alignment = ui->alignmentComboBox->currentData().value<Settings::TextAlignment>();

    if (alignment != m_textAlignment) {
        setAlignment(alignment);
        emit alignmentChanged(alignment);
    }
}

void ScorePropertiesWidget::newRowSelected(int row)
{
    if (m_row == row)
        return;

    setRow(row);
    emit rowChanged(row);
}

