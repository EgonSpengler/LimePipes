/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ASTDEFINES_H
#define ASTDEFINES_H

enum SymbolLength {
    _1 = 1,
    _2 = 2,
    _4 = 4,
    _8 = 8,
    _16 = 16,
    _32 = 32,
    _64 = 64,
    _128 = 128
};

enum SymbolPitch {
    LowG = 1,
    LowA,
    B,
    C,
    D,
    E,
    F,
    HighG,
    HighA
};

enum SymbolType {
    T_Melody,
    T_Bar,
    T_TimeSignature
};

#endif // ASTDEFINES_H
