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
#include <common/defines.h>

namespace Ui {
class SymbolDockWidget;
}

class QListWidgetItem;

class SymbolDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SymbolDockWidget(QWidget *parent = 0);
    explicit SymbolDockWidget(const QString &title, QWidget *parent = 0);
    ~SymbolDockWidget();

    void addListItemToCategory(QListWidgetItem *listItem, SymbolCategory category);

private:
    Ui::SymbolDockWidget *ui;
};

#endif // SYMBOLDOCKWIDGET_H