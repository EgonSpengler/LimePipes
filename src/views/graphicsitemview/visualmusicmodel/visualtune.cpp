/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualtune.h"

VisualTune::VisualTune(QObject *parent)
    : AbstractVisualItem(parent)
{
}

AbstractVisualItem::Type VisualTune::type() const
{
    return AbstractVisualItem::VisualTuneItem;
}

void VisualTune::setDataFromIndex(const QPersistentModelIndex &index)
{
}
