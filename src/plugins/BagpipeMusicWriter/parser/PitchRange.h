/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PITCHRANGE_H
#define PITCHRANGE_H

#include <QDebug>

#include "ast/AstDefines.h"

class PitchRange
{
public:
    explicit PitchRange();
    explicit PitchRange(SymbolPitch startPitch, SymbolPitch endPitch);

    bool isValid() const;

    bool contains(SymbolPitch pitch) const;

    SymbolPitch startPitch() const;
    void setStartPitch(const SymbolPitch &startPitch);

    SymbolPitch endPitch() const;
    void setEndPitch(const SymbolPitch &endPitch);

    static bool checkPitchRange(SymbolPitch startPitch, SymbolPitch endPitch);

private:
    SymbolPitch m_startPitch;
    SymbolPitch m_endPitch;
};

uint qHash(const PitchRange &key);
bool operator ==(const PitchRange &left, const PitchRange &right);
QDebug operator<<(QDebug dbg, const PitchRange &c);

#endif // PITCHRANGE_H
