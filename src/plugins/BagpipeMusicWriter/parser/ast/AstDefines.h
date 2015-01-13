/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ASTDEFINES_H
#define ASTDEFINES_H

#include <QString>

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
    NoPitch,
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

SymbolPitch pitchFromString(const QString &pitch);
QString pitchToString(SymbolPitch pitch);

enum SymbolType {
    T_Melody,
    T_Embellishment,
    T_Bar,
    T_TimeSignature,

    // Group types
    T_Tie
};

#endif // ASTDEFINES_H
