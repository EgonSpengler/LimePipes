/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QPainter>
#include <QDebug>
#include <QPropertyAnimation>

#include <common/graphictypes/glyphitem.h>
#include <common/itemdataroles.h>

#include "symbolgraphicsitem.h"

SymbolGraphicsItem::SymbolGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setInteractionMode(InteractingGraphicsItem::Filter);
    setFlag(QGraphicsItem::ItemIsSelectable);

    m_fadeAnimation = new QPropertyAnimation(this, "opacity", this);
    m_fadeAnimation->setDuration(180);

    m_geometryAnimation = new QPropertyAnimation(this, "geometry", this);
    m_geometryAnimation->setDuration(100);
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
    QPen pen(Qt::red);
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
    if (change == QGraphicsItem::ItemVisibleChange) {
        qDebug() << "Symbol visible change: " << value.toBool();
    }
    if (change == QGraphicsItem::ItemVisibleHasChanged) {
        qDebug() << "Symbol visible has change: " << value.toBool();
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

void SymbolGraphicsItem::fadeIn()
{
    if (!isVisible()) {
        setVisible(true);
    }
    fadeSymbolItem(true);
}

void SymbolGraphicsItem::fadeOut()
{
    if (isVisible()) {
        setVisible(false);
    }
    fadeSymbolItem(false);
}

void SymbolGraphicsItem::fadeSymbolItem(bool in)
{
    int start = 0;
    int end = 1;
    if (!in) {
        int tmp;
        tmp = start;
        start = end;
        end = tmp;
    }

    m_fadeAnimation->setStartValue(start);
    m_fadeAnimation->setEndValue(end);
    m_fadeAnimation->start();
}

void SymbolGraphicsItem::setGeometryAnimated(const QRectF &rect)
{
    if (m_geometryAnimation->state() == QPropertyAnimation::Running) {
        QRectF endGeometry = m_geometryAnimation->endValue().toRectF();
        if (endGeometry != rect) {
            m_geometryAnimation->stop();
            m_geometryAnimation->setStartValue(geometry());
            m_geometryAnimation->setEndValue(rect);
            m_geometryAnimation->start();
        }
    } else {
        m_geometryAnimation->setStartValue(geometry());
        m_geometryAnimation->setEndValue(rect);
        m_geometryAnimation->start();
    }
}

void SymbolGraphicsItem::stopAnimations()
{
    m_geometryAnimation->stop();
}

void SymbolGraphicsItem::setGeometry(const QRectF &rect)
{
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
    if (m_graphicBuilder.isNull()) {
        InteractingGraphicsItem::focusOutEvent(event);
        return;
    }

    GlyphItem *glyph = m_graphicBuilder->glyphItem();
    if (!glyph) {
        InteractingGraphicsItem::focusOutEvent(event);
        return;
    }

    FontColor color = FontColor::Normal;
    if (glyph->isSelected())
        color = FontColor::Selected;

    glyph->setColorRole(color);

    InteractingGraphicsItem::focusOutEvent(event);
}
