/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TEXTPROPERTYEDITWIDGET_H
#define TEXTPROPERTYEDITWIDGET_H

#include <QWidget>

class QFont;
class QColor;
class QString;

namespace Ui {
class TextPropertyEditWidget;
}

class TextPropertyEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextPropertyEditWidget(QWidget *parent = 0);
    ~TextPropertyEditWidget();

    void setText(const QString& text);
    QString text() const;

    void setFont(const QFont& font);
    QFont font() const;

    void setColor(const QColor& color);
    QColor color() const;

public slots:
    void changeText(const QString& text);
    void changeFont(const QFont& font);
    void changeColor(const QColor& color);

signals:
    void textChanged(const QString& newText);
    void fontChanged(const QFont& newFont);
    void colorChanged(const QColor& newColor);

private slots:
    void fontChangeClicked();
    void colorChangeClicked();

private:
    void createConnections();
    Ui::TextPropertyEditWidget *ui;
    QString m_text;
    QFont m_font;
    QColor m_color;
};

#endif // TEXTPROPERTYEDITWIDGET_H
