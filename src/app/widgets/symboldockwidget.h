/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLDOCKWIDGET_H
#define SYMBOLDOCKWIDGET_H

#include <QList>
#include <QDockWidget>

#include <common/interfaces/symbolinterface.h>
#include <common/defines.h>

namespace Ui {
class SymbolDockWidget;
}

class QListWidgetItem;
class SymbolMetaData;

class SymbolDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit SymbolDockWidget(QWidget *parent = 0);
    explicit SymbolDockWidget(const QString &title, QWidget *parent = 0);
    ~SymbolDockWidget();

    void addListItemToCategory(int symbolType, const SymbolMetaData &symbolMeta);

signals:
    void selectedSymbolsChanged(const QList<SymbolBehavior> &symbolBehaviors);

private slots:
    void itemClicked(QListWidgetItem *item);

private:
    void createConnections();
    Ui::SymbolDockWidget *ui;
};

#endif // SYMBOLDOCKWIDGET_H
