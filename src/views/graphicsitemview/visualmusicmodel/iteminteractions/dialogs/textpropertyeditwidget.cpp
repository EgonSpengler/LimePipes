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
    connect(ui->fontPushButton, &QPushButton::clicked,
            this, &TextPropertyEditWidget::fontChangeClicked);
    connect(ui->colorPushButton, &QPushButton::clicked,
            this, &TextPropertyEditWidget::colorChangeClicked);
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

void TextPropertyEditWidget::setFont(const QFont &font)
{
    if (m_font != font)
        m_font = font;
}

QFont TextPropertyEditWidget::font() const
{
    return m_font;
}

void TextPropertyEditWidget::setColor(const QColor &color)
{
    if (m_color != color)
        m_color = color;
}

QColor TextPropertyEditWidget::color() const
{
    return m_color;
}

void TextPropertyEditWidget::changeText(const QString &text)
{
    if (text != m_text) {
        emit textChanged(text);
    }
    setText(text);
}

void TextPropertyEditWidget::fontChangeClicked()
{
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, m_font, this);
    if (ok) {
        changeFont(newFont);
    }
}

void TextPropertyEditWidget::changeFont(const QFont &font)
{
    if (font != m_font) {
        emit fontChanged(font);
    }
    setFont(font);
}

void TextPropertyEditWidget::colorChangeClicked()
{
    QColor newColor = QColorDialog::getColor(m_color, this);
    if (!newColor.isValid())
        return;

    changeColor(newColor);
}

void TextPropertyEditWidget::changeColor(const QColor &color)
{
    if (color != m_color)
        emit colorChanged(color);

    setColor(color);
}
