/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QJsonDocument>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QListWidget>
#include <QDebug>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QIcon>
#include <QToolButton>
#include <QAction>
#include <QActionGroup>

#include <common/graphictypes/glyphitem.h>
#include <common/graphictypes/stemengraver.h>
#include <common/interfaces/symbolinterface.h>
#include <common/datahandling/symbolbehavior.h>
#include <common/graphictypes/symbolgraphicbuilder.h>

#include "symboldockwidget.h"
#include "ui_symboldockwidget.h"

static int IconWidthAndHeight(30);

SymbolDockWidget::SymbolDockWidget(int instrumentType, const PluginManager &pluginManager,
                                   QWidget *parent)
    : QDockWidget(parent),
      ui(new Ui::SymbolDockWidget)
{
    ui->setupUi(this);
    ui->normalListWidget->setIconSize(QSize(IconWidthAndHeight, IconWidthAndHeight));

    m_symbolActionGroup = new QActionGroup(this);
    // An exclusive action group, a checkable action can't be unchecked
    m_symbolActionGroup->setExclusive(false);
    connect(m_symbolActionGroup, &QActionGroup::triggered,
            this, &SymbolDockWidget::symbolActionTriggered);

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
    SymbolBehavior *behavior = pluginManager()->symbolBehaviorForType(symbolType);
    SymbolBehavior behaviorValue;
    if (behavior) {
        behaviorValue = *behavior;
    }
    delete behavior;
    QList<SymbolBehavior> behaviorData({behaviorValue});
    QVariant behaviorVariant = QVariant::fromValue<QList<SymbolBehavior>>(behaviorData);

    QListWidgetItem *widgetItem = 0;
    switch (symbolMeta.category()) {
    case SymbolCategory::Graphical: {
        widgetItem = new QListWidgetItem(symbolMeta.name(),
                                         ui->normalListWidget,
                                         symbolType + QListWidgetItem::UserType);
        QToolButton *itemButton = new QToolButton();
        itemButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        itemButton->setMinimumSize(60, 60);
        QAction *symbolAction = new QAction(symbolMeta.name(), m_symbolActionGroup);
        symbolAction->setCheckable(true);
        symbolAction->setData(behaviorVariant);
        itemButton->setDefaultAction(symbolAction);

        QPixmap glyphPixmap(ui->normalListWidget->iconSize());
        glyphPixmap.fill(Qt::transparent);
        QPainter painter(&glyphPixmap);
        QGraphicsScene scene;

        GlyphItem *glyphItem = 0;
        StemEngraver *stemEngraver = 0;

        SymbolGraphicBuilder *graphicBuilder = m_pluginManager->symbolGraphicBuilderForType(symbolType);
        if (graphicBuilder) {
            stemEngraver = new StemEngraver;
            stemEngraver->insertGraphicsBuilder(0, graphicBuilder);

            foreach (int dataType, graphicBuilder->graphicDataRoles()) {
                graphicBuilder->setData(behaviorValue.data(dataType), dataType);
            }

            glyphItem = graphicBuilder->glyphItem();
            if (glyphItem) {
                scene.addItem(glyphItem);
            }
        }

        scene.render(&painter, QRectF(QPoint(0,0), ui->normalListWidget->iconSize()));
        symbolAction->setIcon(QIcon(glyphPixmap));
        ui->normalListWidget->setItemWidget(widgetItem, itemButton);

        graphicBuilder->deleteLater();
        delete stemEngraver;

        break;
    }
    case SymbolCategory::Spanning: {
        widgetItem = new QListWidgetItem(symbolMeta.name(),
                                         ui->spanningListWidget,
                                         symbolType + QListWidgetItem::UserType);
        widgetItem->setData(Qt::UserRole, behaviorVariant);
        break;
    }
    default:
        break;
    }
}

void SymbolDockWidget::symbolActionTriggered(const QAction *action)
{
    // An exclusive action group, a checkable action can't be unchecked
    // So uncheck all other actions here
    foreach (QAction* groupAction, m_symbolActionGroup->actions()) {
        if (groupAction != action) {
            groupAction->setChecked(false);
        }
    }

    QList<SymbolBehavior> behaviorList = action->data().value<QList<SymbolBehavior>>();
    if (behaviorList.isEmpty())
        return;

    if (action->isChecked()) {
        emit selectedSymbolsChanged(behaviorList);
        int symbolType = behaviorList.at(0).symbolType();
        qDebug() << "SymbolDockWidget: symbol type is checked: " << symbolType;
    } else {
        // If action is not checked, emit empty list
        qDebug() << "SymbolDockWidget: No item checked";
        emit selectedSymbolsChanged(QList<SymbolBehavior>());
    }

}
