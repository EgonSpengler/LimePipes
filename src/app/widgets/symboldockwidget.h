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

#include <common/pluginmanagerinterface.h>
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
    explicit SymbolDockWidget(int instruemntType, const PluginManager &pluginManager,
                              QWidget *parent = 0);
    ~SymbolDockWidget();

    PluginManager pluginManager() const;
    void setPluginManager(const PluginManager &pluginManager);

signals:
    void selectedSymbolsChanged(const QList<SymbolBehavior> &symbolBehaviors);

private slots:
    void itemClicked(QListWidgetItem *item);

private:
    void addListItemToCategory(int symbolType, const SymbolMetaData &symbolMeta);
    void createConnections();
    Ui::SymbolDockWidget *ui;
    PluginManager m_pluginManager;
};

#endif // SYMBOLDOCKWIDGET_H
