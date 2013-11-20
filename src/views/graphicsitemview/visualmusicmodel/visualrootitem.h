/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALROOTITEM_H
#define VISUALROOTITEM_H

#include "visualitem.h"

class VisualRootItem : public VisualItem
{
public:
    explicit VisualRootItem();

    ItemType itemType() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // VISUALROOTITEM_H
