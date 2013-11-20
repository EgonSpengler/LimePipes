/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTABSTRACTVISUALITEM_H
#define TESTABSTRACTVISUALITEM_H

#include <views/graphicsitemview/visualmusicmodel/abstractvisualitem.h>

class TestAbstractVisualItem : public VisualItem
{
public:
    explicit TestAbstractVisualItem();
    virtual ~TestAbstractVisualItem() {}

    ItemType itemType() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // TESTABSTRACTVISUALITEM_H
