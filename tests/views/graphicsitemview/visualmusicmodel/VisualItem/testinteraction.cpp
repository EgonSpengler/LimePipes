/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testinteraction.h"

TestInteraction::TestInteraction(QObject *parent)
    : ItemInteraction(parent)
{
}

void TestInteraction::emitDataChanged(const QVariant& data, int dataRole)
{
    emit dataChanged(data, dataRole);
}
