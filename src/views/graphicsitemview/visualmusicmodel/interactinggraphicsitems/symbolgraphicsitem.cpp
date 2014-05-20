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

SymbolGraphicsItem::SymbolGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setInteractionMode(InteractingGraphicsItem::Filter);
    setFlag(QGraphicsItem::ItemIsSelectable);
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
                glyphItem->setFocusProxy(this);
                glyphItem->setFlag(QGraphicsItem::ItemIsSelectable);
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
    qreal halfStaffSpace = musicFont()->halfStaffSpace();
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
//    if (change == QGraphicsItem::ItemSelectedChange) {
//        bool selected = value.toBool();
//        if (!m_graphicBuilder.isNull()) {
//            FontColor color = FontColor::Normal;
//            if (selected) {
//                color = FontColor::Selected;
//            }
//            m_graphicBuilder->glyphItem()->setColorRole(color);
//        }
//        qDebug() << "Item has selected state: " << selected;
//    }

    return QGraphicsItem::itemChange(change, value);
}

void SymbolGraphicsItem::setGeometry(const QRectF &rect)
{
    QRectF oldGeometry(geometry());
    qDebug() << "Old geometry: " << oldGeometry;
    qDebug() << "Old is null: " << oldGeometry.isNull();

    qDebug() << "New geometry: " << rect;
    InteractingGraphicsItem::setGeometry(rect);
}

void SymbolGraphicsItem::focusInEvent(QFocusEvent *event)
{
    if (m_graphicBuilder.isNull())
        goto parent_implementation;

    m_graphicBuilder->glyphItem()->setColorRole(FontColor::Focus);

parent_implementation:
    InteractingGraphicsItem::focusInEvent(event);
}

void SymbolGraphicsItem::focusOutEvent(QFocusEvent *event)
{
    if (m_graphicBuilder.isNull())
        goto parent_implementation;

    m_graphicBuilder->glyphItem()->setColorRole(FontColor::Normal);

parent_implementation:
    InteractingGraphicsItem::focusOutEvent(event);
}
