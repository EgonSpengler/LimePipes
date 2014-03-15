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
#include <common/pluginmanagerinterface.h>
#include <common/graphictypes/symbolgraphicbuilder.h>
#include "interactinggraphicsitem.h"

class SymbolGraphicsItem : public InteractingGraphicsItem
{
    Q_OBJECT
    friend class SymbolGraphicsItemTest;
public:
    explicit SymbolGraphicsItem(QGraphicsItem *parent = 0);

    // QGraphicsItem interface
    enum { Type = SymbolGraphicItem };
    int type() const { return Type; }

    void setPluginManager(PluginManager pluginManger);
    PluginManager pluginManger() const;

    void setLineHeight(int lineHeigth);
    int lineHeight() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // InteractingGraphicsItem interface
    void setData(const QVariant &value, int key);

private:
    void setGraphicBuilder(SymbolGraphicBuilder *symbolGraphicBuilder);
    SymbolGraphicBuilder *graphicBuilder() const;

    QSharedPointer<SymbolGraphicBuilder> m_graphicBuilder;
    PluginManager m_pluginManager;
};

#endif // SYMBOLGRAPHICSITEM_H
