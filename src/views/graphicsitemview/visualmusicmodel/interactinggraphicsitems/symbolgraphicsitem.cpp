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
    setInteractionMode(InteractingGraphicsItem::Filter);
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
}

PluginManager SymbolGraphicsItem::pluginManger() const
{
    return m_pluginManager;
}

void SymbolGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Bounding rect
//    QPen pen(Qt::red);
//    pen.setWidthF(1.0);
//    painter->setPen(pen);
//    painter->drawRect(boundingRect());
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
        if (graphicBuilder) {
            setGraphicBuilder(graphicBuilder);

            GlyphItem *glyphItem = graphicBuilder->glyphItem();
            if (glyphItem) {
                glyphItem->setParentItem(this);
                setMaximumWidthForGlyphItem(glyphItem);
            }
        }
    }
    if (key == LP::SymbolPitch) {
        PitchPtr pitch = value.value<PitchPtr>();
        setGlyphItemYPosForPitch(pitch);
    }
    if (!m_graphicBuilder.isNull()) {
        m_graphicBuilder->setData(value, key);
        if (m_graphicBuilder->graphicDataRoles().contains(key)) {
            setMaximumWidthForGlyphItem(m_graphicBuilder->glyphItem());
        }
    }

    InteractingGraphicsItem::setData(value, key);
}

void SymbolGraphicsItem::setGlyphItemYPosForPitch(const PitchPtr &pitch)
{
    if (m_graphicBuilder.isNull())
        return;

    GlyphItem *glyph = m_graphicBuilder->glyphItem();
    qreal halfStaffSpace = smufl()->halfStaffSpace();
    glyph->setY(halfStaffSpace * pitch->staffPos());
}

void SymbolGraphicsItem::setMaximumWidthForGlyphItem(GlyphItem *glyphItem)
{
    if (!glyphItem)
        return;

    qreal maxWidth = glyphItem->boundingRect().width();
    setMaximumWidth(maxWidth);
}

QVariant SymbolGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSceneHasChanged) {
        if (scene()) { // If this item was initially added to a scene,
                       // install this item as scene event filter
            if (!m_graphicBuilder.isNull()) {
                GlyphItem *glyphItem = m_graphicBuilder->glyphItem();
                if (glyphItem) {
                    glyphItem->installSceneEventFilter(this);
                }
            }
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
