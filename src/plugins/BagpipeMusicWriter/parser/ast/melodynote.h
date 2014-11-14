/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTE_H
#define MELODYNOTE_H

#include <QHash>
#include <QString>

#include "AstDefines.h"
#include "symbol.h"

class MelodyNote : public Symbol
{
public:
    explicit MelodyNote(const QString &bwwCode, MusicItem *parent=0);

    SymbolLength length() const;
    void setLength(const SymbolLength &length);

    SymbolPitch pitch() const;
    void setPitch(const SymbolPitch &pitch);

private:
    void setNoteFromBww(const QString &bwwCode);
    static QHash<QString, SymbolPitch> s_melodyNoteMap;
    static QHash<QString, SymbolPitch> initMelodyNoteMap();

    SymbolLength m_length;
    SymbolPitch m_pitch;
};

#endif // MELODYNOTE_H
