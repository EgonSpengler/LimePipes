/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "abstractvisualitem.h"

AbstractVisualItem::AbstractVisualItem(QObject *parent)
    : QObject(parent)
{
}

void AbstractVisualItem::insertItem(int row, AbstractVisualItem *item)
{
    m_childItems.insert(row, item);
}

int AbstractVisualItem::childItemCount()
{
    return m_childItems.count();
}

AbstractVisualItem *AbstractVisualItem::childItemAt(int row)
{
    if (isValidIndex(row))
        return m_childItems.at(row);
    return 0;
}

void AbstractVisualItem::removeItemAt(int row)
{
    if (isValidIndex(row))
        m_childItems.removeAt(row);
}

bool AbstractVisualItem::isValidIndex(int row)
{
    if (row >= 0 && row < m_childItems.count())
        return true;
    return false;
}
