/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PITCHCONTEXT_H
#define PITCHCONTEXT_H

#include <QStringList>
#include <QMap>
#include <QSharedPointer>
#include <model/datatypes/pitch.h>

class PitchContext
{
public:
    explicit PitchContext();

    int lowestStaffPos() const;
    int highestStaffPos() const;
    QStringList pitchNames() const;
    PitchPtr pitchForName( const QString &name ) const;
    PitchPtr pitchForStaffPos( int staffPos ) const;
    void insertPitch( int staffPos, const QString &name );

private:
    QMap<int, PitchPtr> m_pitches;
};

typedef QSharedPointer<PitchContext> PitchContextPtr;

#endif // PITCHCONTEXT_H
