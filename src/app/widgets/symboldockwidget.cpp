/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QListWidgetItem>
#include <QListWidget>
#include <QDebug>

#include <common/interfaces/symbolinterface.h>
#include <common/datahandling/symbolbehavior.h>

#include "symboldockwidget.h"
#include "ui_symboldockwidget.h"

SymbolDockWidget::SymbolDockWidget(int instrumentType, const PluginManager &pluginManager,
                                   QWidget *parent)
    : QDockWidget(parent),
      ui(new Ui::SymbolDockWidget)
{
    ui->setupUi(this);

    setPluginManager(pluginManager);

    InstrumentMetaData instrumentMeta = pluginManager->instrumentMetaData(instrumentType);
    setWindowTitle(instrumentMeta.name());
    createConnections();

    QList<int> symbolTypes = instrumentMeta.supportedSymbols();
    foreach (int type, symbolTypes) {
        SymbolMetaData metaData = pluginManager->symbolMetaData(type);
        addListItemToCategory(type, metaData);
    }
}

void SymbolDockWidget::createConnections()
{
    connect(ui->normalListWidget, &QListWidget::itemClicked,
            [this] (QListWidgetItem *item) {
        ui->spanningListWidget->selectionModel()->clear();
        itemClicked(item);
    });
    connect(ui->spanningListWidget, &QListWidget::itemClicked,
            [this] (QListWidgetItem *item) {
        ui->normalListWidget->selectionModel()->clear();
        itemClicked(item);
    });
}
PluginManager SymbolDockWidget::pluginManager() const
{
    return m_pluginManager;
}

void SymbolDockWidget::setPluginManager(const PluginManager &pluginManager)
{
    m_pluginManager = pluginManager;
}


SymbolDockWidget::~SymbolDockWidget()
{
    delete ui;
}

void SymbolDockWidget::addListItemToCategory(int symbolType, const SymbolMetaData &symbolMeta)
{
    switch (symbolMeta.category()) {
    case SymbolCategory::Graphical: {
        new QListWidgetItem(symbolMeta.name(),
                            ui->normalListWidget,
                            symbolType + QListWidgetItem::UserType);
        break;
    }
    case SymbolCategory::Spanning: {
        new QListWidgetItem(symbolMeta.name(),
                            ui->spanningListWidget,
                            symbolType + QListWidgetItem::UserType);
        break;
    }
    default:
        break;
    }
}

void SymbolDockWidget::itemClicked(QListWidgetItem *item)
{
    int symbolType = item->type();
    symbolType -= QListWidgetItem::UserType;
    qDebug() << "SymbolDockWidget: Clicked symbol type " << symbolType;
}
