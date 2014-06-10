/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGRAPHICSITEM_H
#define SYMBOLGRAPHICSITEM_H

#include <QSharedPointer>
#include <common/defines.h>
#include <common/datatypes/pitch.h>
#include <common/pluginmanagerinterface.h>
#include <common/graphictypes/symbolgraphicbuilder.h>
#include "interactinggraphicsitem.h"

class GlyphItem;
class QPropertyAnimation;

class SymbolGraphicsItem : public InteractingGraphicsItem
{
    Q_OBJECT
    friend class SymbolGraphicsItemTest;
public:
    explicit SymbolGraphicsItem(QGraphicsItem *parent = 0);

    // QGraphicsItem interface
    enum { Type = SymbolGraphicsItemType };
    int type() const { return Type; }

    void setPluginManager(PluginManager pluginManger);
    PluginManager pluginManger() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // InteractingGraphicsItem interface
    void setData(const QVariant &value, int key);

    void setGeometry(const QRectF &rect);

    void fadeIn();
    void fadeOut();

    void setGeometryAnimated(const QRectF& rect);

    void stopAnimations();

    SymbolGraphicBuilder *graphicBuilder() const;

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void musicFontHasChanged(const MusicFontPtr &musicFont);

private:
    void setGraphicBuilder(SymbolGraphicBuilder *symbolGraphicBuilder);
    void setGlyphItemYPosForPitch(const PitchPtr &pitch);
    void setMaximumWidthForGlyphItem(GlyphItem *glyphItem);
    void fadeSymbolItem(bool in);

    QSharedPointer<SymbolGraphicBuilder> m_graphicBuilder;
    PluginManager m_pluginManager;
    QPropertyAnimation *m_fadeAnimation;
    QPropertyAnimation *m_geometryAnimation;
    QRectF m_geometryAfterAnimation;
};

#endif // SYMBOLGRAPHICSITEM_H
