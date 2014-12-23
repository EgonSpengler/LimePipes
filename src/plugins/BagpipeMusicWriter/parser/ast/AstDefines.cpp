/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "AstDefines.h"


SymbolPitch pitchFromString(const QString &pitch)
{
    if (pitch == QStringLiteral("LowG")) return LowG;
    if (pitch == QStringLiteral("LowA")) return LowA;
    if (pitch == QStringLiteral("B")) return B;
    if (pitch == QStringLiteral("C")) return C;
    if (pitch == QStringLiteral("D")) return D;
    if (pitch == QStringLiteral("E")) return E;
    if (pitch == QStringLiteral("F")) return F;
    if (pitch == QStringLiteral("HighG")) return HighG;
    if (pitch == QStringLiteral("HighA")) return HighA;
    if (pitch == QStringLiteral("No Pitch")) return NoPitch;

    return NoPitch;
}


QString pitchToString(SymbolPitch pitch)
{
    switch (pitch) {
    case NoPitch:
        return QStringLiteral("No Pitch");
    case LowG:
        return QStringLiteral("LowG");
    case LowA:
        return QStringLiteral("LowA");
    case B:
        return QStringLiteral("B");
    case C:
        return QStringLiteral("C");
    case D:
        return QStringLiteral("D");
    case E:
        return QStringLiteral("E");
    case F:
        return QStringLiteral("F");
    case HighG:
        return QStringLiteral("HighG");
    case HighA:
        return QStringLiteral("HighA");
    }

    return QStringLiteral("No Pitch");
}
