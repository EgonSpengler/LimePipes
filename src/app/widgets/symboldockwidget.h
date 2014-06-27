/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLDOCKWIDGET_H
#define SYMBOLDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class SymbolDockWidget;
}

class SymbolDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SymbolDockWidget(QWidget *parent = 0);
    ~SymbolDockWidget();

private:
    Ui::SymbolDockWidget *ui;
};

#endif // SYMBOLDOCKWIDGET_H
