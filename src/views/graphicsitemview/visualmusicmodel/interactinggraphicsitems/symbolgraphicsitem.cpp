/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include <QDebug>
#include <common/graphictypes/glyphitem.h>
#include <common/itemdataroles.h>
#include "symbolgraphicsitem.h"

using namespace LP::View;

SymbolGraphicsItem::SymbolGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent)
{
    m_glyphItem = new GlyphItem("noteheadBlack", this);
}

void SymbolGraphicsItem::setGraphicBuilder(SymbolGraphicBuilder *symbolGraphicBuilder)
{
    m_graphicBuilder.reset(symbolGraphicBuilder);
}

SymbolGraphicBuilder *SymbolGraphicsItem::graphicBuilder() const
{
    return m_graphicBuilder.data();
}

void SymbolGraphicsItem::setPluginManager(PluginManager pluginManger)
{
    m_pluginManager = pluginManger;

    m_glyphItem->setSmufl(m_pluginManager->smufl());
}

PluginManager SymbolGraphicsItem::pluginManger() const
{
    return m_pluginManager;
}

void SymbolGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    if (!m_graphicBuilder.isNull()) {
//        painter->drawPixmap(0, 0, m_graphicBuilder->symbolGraphic()->pixmap());
//    }
}

void SymbolGraphicsItem::setData(const QVariant &value, int key)
{
    if (!value.isValid())
        return;

    if (key == LP::SymbolType) {
        if (m_pluginManager.isNull()) {
            qWarning() << QLatin1String("Plugin manager isn't set, can't get graphic builder");
            return;
        }
        SymbolGraphicBuilder *graphicBuilder = m_pluginManager->symbolGraphicBuilderForType(value.toInt());
        setGraphicBuilder(graphicBuilder);
    }
    if (!m_graphicBuilder.isNull()) {
        m_graphicBuilder->setData(value, key);
    }
}
