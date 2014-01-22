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
      m_childItemToInsert(0),
      m_rowOfChildToInsert(-1)
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

void TestVisualItem::setData(const QVariant &value, int key)
{
    VisualItem::setData(value, key);
    m_data.insert(key, value);
}

bool TestVisualItem::hasData(int key)
{
    return m_data.contains(key);
}

QVariant TestVisualItem::data(int key)
{
    return m_data.value(key);
}

void TestVisualItem::insertChildItem(int index, VisualItem *childItem)
{
    VisualItem::insertChildItem(index, childItem);

    m_insertChildItemCalled = true;
    m_rowOfChildToInsert = index;
    m_childItemToInsert = childItem;
}
