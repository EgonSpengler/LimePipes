/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualtune.h"

VisualTune::VisualTune(QObject *parent)
    : VisualItem(parent)
{
}

VisualItem::ItemType VisualTune::itemType() const
{
    return VisualItem::VisualTuneItem;
}

void VisualTune::setDataFromIndex(const QPersistentModelIndex &index)
{
}
