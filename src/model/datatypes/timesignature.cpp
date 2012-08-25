/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "timesignature.h"

int TimeSignature::beatCount(TimeSignature::Type type)
{
    switch (type) {
    case _2_2:
    case _2_4:
        return 2;
    case _3_4:
    case _3_8:
        return 3;
    case _4_4:
        return 4;
    case _6_8:
        return 6;
    case _9_8:
        return 9;
    case _12_8:
        return 12;
    }
}

int TimeSignature::beatUnit(TimeSignature::Type type)
{
    switch (type) {
    case _2_2:
        return 2;
    case _2_4:
    case _3_4:
    case _4_4:
        return 4;
    case _3_8:
    case _6_8:
    case _9_8:
    case _12_8:
        return 8;
    }
}
