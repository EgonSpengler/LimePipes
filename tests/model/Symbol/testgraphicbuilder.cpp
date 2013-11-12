/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testgraphicbuilder.h"

TestGraphicBuilder::TestGraphicBuilder(MusicItem *item, QObject *parent)
    : QObject(parent),
      SymbolGraphicBuilder(item)
{
}

void TestGraphicBuilder::createPixmaps(int lineHeight)
{
    Q_UNUSED(lineHeight)
    emit createPixmapsCalled();
}
