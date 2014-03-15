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
#include <common/graphictypes/symbolgraphicbuilder.h>
#include "interactinggraphicsitem.h"

class SymbolGraphicsItem : public InteractingGraphicsItem
{
public:
    explicit SymbolGraphicsItem(QGraphicsItem *parent = 0);

    // QGraphicsItem interface
    enum { Type = SymbolGraphicItem };
    int type() const { return Type; }

    void setGraphicBuilder(SymbolGraphicBuilder *symbolGraphicBuilder);
    SymbolGraphicBuilder *graphicBuilder() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // InteractingGraphicsItem interface
    void setData(const QVariant &value, int key);

private:
    QSharedPointer<SymbolGraphicBuilder> m_graphicBuilder;
};

#endif // SYMBOLGRAPHICSITEM_H
