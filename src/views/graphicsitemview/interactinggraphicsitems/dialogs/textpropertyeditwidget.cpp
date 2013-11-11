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

TextPropertyEditWidget::~TextPropertyEditWidget()
{
    delete ui;
}

QString TextPropertyEditWidget::text() const
{
    return ui->lineEdit->text();
}

QFont TextPropertyEditWidget::font() const
{
    return m_font;
}

QColor TextPropertyEditWidget::color() const
{
    return m_color;
}

void TextPropertyEditWidget::setText(const QString &text)
{
    if (ui->lineEdit->text() != text)
        ui->lineEdit->setText(text);
}

void TextPropertyEditWidget::fontChangeClicked()
{
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, m_font, this);
    if (ok) {
        m_font = newFont;
        emit fontChanged(newFont);
    }
}

void TextPropertyEditWidget::colorChangeClicked()
{
    QColor newColor = QColorDialog::getColor(m_color, this);
    if (!newColor.isValid())
        return;

    m_color = newColor;
    emit colorChanged(newColor);
}

void TextPropertyEditWidget::createConnections()
{
    connect(ui->lineEdit, SIGNAL(textChanged(QString)),
            this, SIGNAL(textChanged(QString)));
    connect(ui->fontPushButton, SIGNAL(clicked()),
            this, SLOT(fontChangeClicked()));
    connect(ui->colorPushButton, SIGNAL(clicked()),
            this, SLOT(colorChangeClicked()));
}
