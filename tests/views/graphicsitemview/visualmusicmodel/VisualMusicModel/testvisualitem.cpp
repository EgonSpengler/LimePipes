/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testvisualitem.h"

TestVisualItem::TestVisualItem(QObject *parent)
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
