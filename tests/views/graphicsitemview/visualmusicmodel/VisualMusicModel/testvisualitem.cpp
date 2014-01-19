/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testvisualitem.h"

TestVisualItem::TestVisualItem(QObject *parent)
    : VisualItem(parent),
      m_insertChildItemCalled(false),
      m_rowOfChildToInsert(-1),
      m_childItemToInsert(0)
{
}

void TestVisualItem::emitDataChanged(const QVariant &data, int dataRole)
{
    emit dataChanged(data, dataRole);
}

void TestVisualItem::emitRowSequenceChanged()
{
    emit rowSequenceChanged();
}

void TestVisualItem::insertChildItem(int index, VisualItem *childItem)
{
    m_insertChildItemCalled = true;
    m_rowOfChildToInsert = index;
    m_childItemToInsert = childItem;
}
