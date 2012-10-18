/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class Bar
  * A @ref Symbol "Bar symbol" represents the vertical bar line in a Staff.
  */

#include "bar.h"

Bar::Bar()
    : Symbol(LP::Bar,  tr("Bar"))
{
}
