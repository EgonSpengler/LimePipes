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
#include <QMetaType>
#include <QDockWidget>
#include <QHash>

#include <common/pluginmanagerinterface.h>
#include <common/interfaces/symbolinterface.h>
#include <common/defines.h>

namespace Ui {
class SymbolDockWidget;
}

class QListWidgetItem;
class SymbolMetaData;
class QActionGroup;

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
    void symbolActionTriggered(const QAction *action);

private:
    void addListItemToCategory(int symbolType, const SymbolMetaData &symbolMeta);
    void createConnections();
    Ui::SymbolDockWidget *ui;
    PluginManager m_pluginManager;
    QActionGroup *m_symbolActionGroup;
};

Q_DECLARE_METATYPE(QList<SymbolBehavior>)

#endif // SYMBOLDOCKWIDGET_H
