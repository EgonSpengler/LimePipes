/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TEXTEDITHEADERWIDGET_H
#define TEXTEDITHEADERWIDGET_H

#include <QFrame>

namespace Ui {
class TextEditHeaderWidget;
}

class TextEditHeaderWidget : public QFrame
{
    Q_OBJECT
public:
    explicit TextEditHeaderWidget(QWidget *parent = 0);
    ~TextEditHeaderWidget();

    void addTextPluginName(const QString &name);
    void selectTextPluginName(const QString &name);
    QString selectedTextPluginName() const;

signals:
    void textPluginNameChanged(const QString &name);

private:
    Ui::TextEditHeaderWidget *ui;
};

#endif // TEXTEDITHEADERWIDGET_H
