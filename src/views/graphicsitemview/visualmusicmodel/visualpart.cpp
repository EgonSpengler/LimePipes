/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualpart.h"

VisualPart::VisualPart(QObject *parent)
    : QObject(parent)
{
}

AbstractVisualItem::Type VisualPart::type() const
{
    return AbstractVisualItem::VisualPartItem;
}

void VisualPart::setDataFromIndex(const QPersistentModelIndex &index)
{
}
