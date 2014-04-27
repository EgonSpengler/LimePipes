/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pitchcontext.h"

PitchContext::PitchContext()
{
    m_pitches.insert(0, PitchPtr(new Pitch(0, "No pitch")));
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
    foreach (PitchPtr pitch, m_pitches) {
        pitchNames << pitch->name();
    }
    return pitchNames;
}

PitchPtr PitchContext::pitchForName(const QString &name) const
{
    foreach (PitchPtr pitch, m_pitches) {
        if (pitch->name() == name) {
            return pitch;
        }
    }

    if (!name.isEmpty()) {
        qWarning("pitchname not in context");
    }

    return PitchPtr(new Pitch(0, "no pitch"));
}

PitchPtr PitchContext::pitchForStaffPos(int staffPos) const
{
    return m_pitches.value(staffPos, PitchPtr(new Pitch(0, "no pitch")));
}

void PitchContext::insertPitch(int staffPos, const QString &name)
{
    m_pitches.insert(staffPos, PitchPtr(new Pitch(staffPos, name)));
}
