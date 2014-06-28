/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PITCHCONTEXT_H
#define PITCHCONTEXT_H

#include <QMap>
#include <QStringList>
#include <QSharedPointer>
#include <QVariant>
#include <common/defines.h>
#include "pitch.h"

class PitchContext
{
public:
    explicit PitchContext();

    int lowestStaffPos() const;
    int highestStaffPos() const;

    QStringList pitchNames() const;

    Pitch pitchForName(const QString &name) const;
    Pitch pitchForStaffPos(int staffPos) const;

    StaffType staffType() const;
    void setStaffType(const StaffType &staffType);

    ClefType defaultClef() const;
    void setDefaultClef(const ClefType &defaultClef);

protected:
    void insertPitch(int staffPos, const QString &name);

private:
    QMap<int, Pitch> m_pitches;
    StaffType m_staffType;
    ClefType m_defaultClef;
};

typedef QSharedPointer<PitchContext> PitchContextPtr;

Q_DECLARE_METATYPE(PitchContextPtr)

#endif // PITCHCONTEXT_H
