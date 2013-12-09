/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTINTERACTINGITEM_H
#define TESTINTERACTINGITEM_H

#include <views/graphicsitemview/visualmusicmodel/interactinggraphicsitems/interactinggraphicsitem.h>

class TestInteractingItem : public InteractingGraphicsItem
{
    Q_OBJECT
public:
    explicit TestInteractingItem(QGraphicsItem *parent = 0);

signals:
    void setDataCalled();
    void insertChildItemCalled();

public:
    void insertChildItem(int index, InteractingGraphicsItem *childItem);
    void setData(const QVariant &value, int key);
};

#endif // TESTINTERACTINGITEM_H
