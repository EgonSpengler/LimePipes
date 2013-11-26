/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ABSTRACTVISUALITEMFACTORY_H
#define ABSTRACTVISUALITEMFACTORY_H

#include "visualitem.h"

class AbstractVisualItemFactory
{
public:
    explicit AbstractVisualItemFactory() {}
    virtual ~AbstractVisualItemFactory() {}

    virtual VisualItem *createVisualItem(VisualItem::ItemType type) = 0;
};

#endif // ABSTRACTVISUALITEMFACTORY_H
