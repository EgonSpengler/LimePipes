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
    friend class TextPropertyEditWidgetTest;

    Q_OBJECT

public:
    explicit TextPropertyEditWidget(QWidget *parent = 0);
    ~TextPropertyEditWidget();

    void setText(const QString& text);
    QString text() const;

public slots:
    void changeText(const QString& text);

signals:
    void textChanged(const QString& newText);

private:
    void createConnections();
    Ui::TextPropertyEditWidget *ui;
    QString m_text;
    QFont m_font;
    QColor m_color;
};

#endif // TEXTPROPERTYEDITWIDGET_H
