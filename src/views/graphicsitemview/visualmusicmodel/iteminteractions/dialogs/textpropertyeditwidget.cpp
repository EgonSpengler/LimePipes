/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QFontDialog>
#include <QColorDialog>
#include "textpropertyeditwidget.h"
#include "ui_textpropertyeditwidget.h"

TextPropertyEditWidget::TextPropertyEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextPropertyEditWidget)
{
    ui->setupUi(this);

    createConnections();
}

void TextPropertyEditWidget::createConnections()
{
    connect(ui->lineEdit, &QLineEdit::textChanged,
            this, &TextPropertyEditWidget::changeText);
}

TextPropertyEditWidget::~TextPropertyEditWidget()
{
    delete ui;
}

void TextPropertyEditWidget::setText(const QString &text)
{
    if (m_text != text) {
        m_text = text;
        ui->lineEdit->setText(text);
    }
}

QString TextPropertyEditWidget::text() const
{
    return m_text;
}

void TextPropertyEditWidget::changeText(const QString &text)
{
    if (text != m_text) {
        setText(text);
        emit textChanged(text);
    }
}
