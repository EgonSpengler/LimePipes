/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>
#include <QStringList>


#include "melodynote.h"

QHash<QString, SymbolPitch> MelodyNote::s_melodyNoteMap(MelodyNote::initMelodyNoteMap());

MelodyNote::MelodyNote(const QString &bwwCode, MusicItem *parent)
    : Symbol(T_Melody, parent),
      m_length(_4),
      m_pitch(LowA),
      m_dots(0)
{
    setNoteFromBww(bwwCode);
}

void MelodyNote::setNoteFromBww(const QString &bwwCode)
{
    QStringList melodynoteParts(bwwCode.split(QLatin1Char('_')));
    if (!melodynoteParts.count() == 2) {
        qWarning() << "Can't add melody note: " << bwwCode;
        return;
    }

    QString pitchName(melodynoteParts.first());
    if (pitchName.endsWith(QLatin1Char('l')) ||
            pitchName.endsWith(QLatin1Char('r'))) {
        pitchName = pitchName.remove(pitchName.length() - 1, 1);
    }

    if (!s_melodyNoteMap.contains(pitchName)) {
        qWarning() << "Can't find melody note in map: " << melodynoteParts.first();
        return;
    }

    setPitch(s_melodyNoteMap.value(pitchName));
    setLength(static_cast<SymbolLength>(melodynoteParts.last().toInt()));
}

QHash<QString, SymbolPitch> MelodyNote::initMelodyNoteMap()
{
    QHash<QString, SymbolPitch> noteMap;
    noteMap.insert(QStringLiteral("LG"), LowG);
    noteMap.insert(QStringLiteral("LA"), LowA);
    noteMap.insert(QStringLiteral("B"), B);
    noteMap.insert(QStringLiteral("C"), C);
    noteMap.insert(QStringLiteral("D"), D);
    noteMap.insert(QStringLiteral("E"), E);
    noteMap.insert(QStringLiteral("F"), F);
    noteMap.insert(QStringLiteral("HG"), HighG);
    noteMap.insert(QStringLiteral("HA"), HighA);
    return noteMap;
}
quint8 MelodyNote::dots() const
{
    return m_dots;
}

void MelodyNote::setDots(const quint8 &dots)
{
    m_dots = dots;
}

SymbolPitch MelodyNote::pitch() const
{
    return m_pitch;
}

void MelodyNote::setPitch(const SymbolPitch &pitch)
{
    m_pitch = pitch;
}

SymbolLength MelodyNote::length() const
{
    return m_length;
}

void MelodyNote::setLength(const SymbolLength &length)
{
    m_length = length;
}

