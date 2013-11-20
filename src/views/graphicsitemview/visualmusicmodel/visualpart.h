/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALPART_H
#define VISUALPART_H

#include <QObject>
#include "visualitem.h"

class VisualPart : public VisualItem
{
public:
    explicit VisualPart(QObject *parent = 0);

    ItemType itemType() const;
    void setDataFromIndex(const QPersistentModelIndex &index);
};

#endif // VISUALPART_H
