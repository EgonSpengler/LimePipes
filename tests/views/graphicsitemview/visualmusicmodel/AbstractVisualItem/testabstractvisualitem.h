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

class TestAbstractVisualItem : public AbstractVisualItem
{
public:
    explicit TestAbstractVisualItem();
    virtual ~TestAbstractVisualItem() {}

    Type type() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // TESTABSTRACTVISUALITEM_H
