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

    QFont font() const;
    QColor color() const;

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
    QFont m_font;
    QColor m_color;
};

#endif // TEXTPROPERTYEDITWIDGET_H
