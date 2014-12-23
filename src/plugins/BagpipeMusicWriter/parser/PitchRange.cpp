/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "PitchRange.h"

uint qHash(const PitchRange &key)
{
    return (static_cast<uint>(key.startPitch()) +
            static_cast<uint>(key.endPitch()));
}

PitchRange::PitchRange()
    : m_startPitch(NoPitch),
      m_endPitch(NoPitch)
{
}

PitchRange::PitchRange(SymbolPitch startPitch, SymbolPitch endPitch)
{
    if (checkPitchRange(startPitch, endPitch)) {
        m_startPitch = startPitch;
        m_endPitch = endPitch;
    }
}

bool PitchRange::isValid() const
{
    return checkPitchRange(m_startPitch, m_endPitch);
}

bool PitchRange::contains(SymbolPitch pitch) const
{
    if (!isValid()) {
        return false;
    }

    quint32 numPitch = static_cast<quint32>(pitch);
    quint32 numStart = static_cast<quint32>(m_startPitch);
    quint32 numEnd = static_cast<quint32>(m_endPitch);

    if (numPitch >= numStart &&
            numPitch <= numEnd) {
        return true;
    }

    return false;
}

SymbolPitch PitchRange::startPitch() const
{
    return m_startPitch;
}

void PitchRange::setStartPitch(const SymbolPitch &startPitch)
{
    m_startPitch = startPitch;
}

SymbolPitch PitchRange::endPitch() const
{
    return m_endPitch;
}

void PitchRange::setEndPitch(const SymbolPitch &endPitch)
{
    m_endPitch = endPitch;
}

bool PitchRange::checkPitchRange(SymbolPitch startPitch, SymbolPitch endPitch)
{
    if (startPitch == NoPitch ||
            endPitch == NoPitch) {
        return false;
    }

    // A pitch range can consist of the same start and end
    if (startPitch == endPitch) {
        return true;
    }

    quint32 numStart = static_cast<quint32>(startPitch);
    quint32 numEnd = static_cast<quint32>(endPitch);

    if (numEnd < numStart) {
        return false;
    }

    return true;
}

bool operator ==(const PitchRange &left, const PitchRange &right)
{
    if (left.startPitch() == right.startPitch() &&
            left.endPitch() == right.endPitch()) {
        return true;
    }

    return false;
}

QDebug operator<<(QDebug dbg, const PitchRange &range)
{
    dbg.nospace() << "PitchRange (" << pitchToString(range.startPitch()) << "-"
                  << pitchToString(range.endPitch()) << ")";

    return dbg.space();
}
