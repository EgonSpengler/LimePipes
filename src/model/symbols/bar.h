/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef BAR_H
#define BAR_H

#include "symbol.h"
#include "model_itemtypes.h"

class Bar : public Symbol
{
public:
    explicit Bar();
    int type() const { return BarType; }
};

#endif // BAR_H
