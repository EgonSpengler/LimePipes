/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIE_H
#define TIE_H

#include <symbol.h>

class Tie : public Symbol
{
    Q_DECLARE_TR_FUNCTIONS(MelodyNote)
public:
    explicit Tie();
private:
    void initSymbol();
};

#endif // TIE_H
