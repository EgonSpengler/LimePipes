/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "texteditheaderwidget.h"
#include "ui_texteditheaderwidget.h"

TextEditHeaderWidget::TextEditHeaderWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TextEditHeaderWidget)
{
    ui->setupUi(this);

    connect(ui->textPluginComboBox, &QComboBox::currentTextChanged,
            this, &TextEditHeaderWidget::textPluginNameChanged);
}

TextEditHeaderWidget::~TextEditHeaderWidget()
{
    delete ui;
}

void TextEditHeaderWidget::addTextPluginName(const QString &name)
{
    ui->textPluginComboBox->addItem(name);
}

void TextEditHeaderWidget::selectTextPluginName(const QString &name)
{
    ui->textPluginComboBox->setCurrentText(name);
}

QString TextEditHeaderWidget::selectedTextPluginName() const
{
    return ui->textPluginComboBox->currentText();
}
