/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pageviewdummy.h"

PageViewDummy::PageViewDummy()
{
}

int PageViewDummy::pageCount() const
{
    return 0;
}

int PageViewDummy::rowCount() const
{
    return m_graphicWidgets.count();
}

int PageViewDummy::rowCountOfPage(int index) const
{
    return 0;
}

void PageViewDummy::appendRow(QGraphicsWidget *row)
{
    m_graphicWidgets.append(row);
}

void PageViewDummy::prependRow(QGraphicsWidget *row)
{
    m_graphicWidgets.prepend(row);
}

void PageViewDummy::insertRow(int index, QGraphicsWidget *row)
{
    m_graphicWidgets.insert(index, row);
}

void PageViewDummy::removeRow(int rowIndex)
{
    m_graphicWidgets.removeAt(rowIndex);
}

QGraphicsWidget *PageViewDummy::rowAt(int index) const
{
    return m_graphicWidgets.at(index);
}
