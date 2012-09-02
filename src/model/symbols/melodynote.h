/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTE_H
#define MELODYNOTE_H

#include <symbol.h>

class MelodyNote : public Symbol
{
public:
    explicit MelodyNote()
        : Symbol(LP::MelodyNote) {}

};

#endif // MELODYNOTE_H
