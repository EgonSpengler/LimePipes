/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class RootItem
  * The root item of the tree of @ref MusicItem "MusicItems".
  */

#include "rootitem.h"

bool RootItem::itemSupportsWritingOfData(int role) const
{
    Q_UNUSED(role)
    return false;
}
