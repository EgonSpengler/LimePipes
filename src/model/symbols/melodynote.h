/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTE_H
#define MELODYNOTE_H

#include <QCoreApplication>

#include <symbol.h>

class MelodyNote : public Symbol
{
    Q_DECLARE_TR_FUNCTIONS(MelodyNote)
public:
    explicit MelodyNote()
        : Symbol(LP::MelodyNote, tr("Melody Note")) {}
    MelodyNote(int type, const QString &name)
        : Symbol(type, name) {}
};

#endif // MELODYNOTE_H
