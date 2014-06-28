/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TIE_H
#define TIE_H

#include <symbol.h>

class Tie : public Symbol
{
    Q_DECLARE_TR_FUNCTIONS(MelodyNote)
public:
    explicit Tie(const QString &name);
private:
    void initSymbol();

    // MusicItem interface
public:
    bool itemSupportsWritingOfData(int role) const;
};

#endif // TIE_H
