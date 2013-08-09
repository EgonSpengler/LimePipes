/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ABSTRACTVISUALITEM_H
#define ABSTRACTVISUALITEM_H

#include <QPersistentModelIndex>
#include "visualiteminterface.h"

class AbstractVisualItem : public VisualItemInterface
{
public:
    enum Type {
        VisualRootItem,
        VisualScoreItem,
        VisualTuneItem,
        VisualPartItem,
        VisualMeasureItem,
        VisualSymbolItem
    };

    virtual Type type() const = 0;
    virtual void setDataFromIndex(const QPersistentModelIndex& index) = 0;

    explicit AbstractVisualItem();
};

#endif // ABSTRACTVISUALITEM_H
