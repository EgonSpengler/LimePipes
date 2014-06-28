/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pitchcontext.h"

PitchContext::PitchContext()
    : m_staffType(StaffType::Standard)
{
    m_pitches.insert(0, Pitch(0, "No pitch"));
}

/*!
 * \brief PitchContext::lowestStaffPos Returns the staff position of the lowest pitch.
 *        This is the staff pos with the highest number.
 * \return
 */
int PitchContext::lowestStaffPos() const
{
    int highestIndex = m_pitches.count() - 1;
    if (highestIndex >= 0) {
        return m_pitches.keys().at(highestIndex);
    }
    return 0;
}

/*!
 * \brief PitchContext::highestStaffPos Returns the staff position of the highest pitch.
 *        This is the staff pos with the lowest number.
 * \return
 */
int PitchContext::highestStaffPos() const
{
    return m_pitches.keys().at(0);
}

QStringList PitchContext::pitchNames() const
{
    QStringList pitchNames;
    foreach (Pitch pitch, m_pitches) {
        pitchNames << pitch.name();
    }
    return pitchNames;
}

Pitch PitchContext::pitchForName(const QString &name) const
{
    foreach (Pitch pitch, m_pitches) {
        if (pitch.name() == name) {
            return pitch;
        }
    }

    if (!name.isEmpty()) {
        qWarning("pitchname not in context");
    }

    return Pitch();
}

Pitch PitchContext::pitchForStaffPos(int staffPos) const
{
    return m_pitches.value(staffPos, Pitch(0, "no pitch"));
}

void PitchContext::insertPitch(int staffPos, const QString &name)
{
    m_pitches.insert(staffPos, Pitch(staffPos, name));
}

ClefType PitchContext::defaultClef() const
{
    return m_defaultClef;
}

void PitchContext::setDefaultClef(const ClefType &defaultClef)
{
    m_defaultClef = defaultClef;
}

StaffType PitchContext::staffType() const
{
    return m_staffType;
}

void PitchContext::setStaffType(const StaffType &staffType)
{
    m_staffType = staffType;
}

