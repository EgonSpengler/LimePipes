/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOLGROUP_H
#define SYMBOLGROUP_H

#include "symbol.h"

class SymbolGroup : public Symbol
{
public:
    explicit SymbolGroup(SymbolType type, MusicItem *parent=0);
    virtual ~SymbolGroup();

    void accept(AstVisitorInterface *visitor);

    bool closed() const;
    void setClosed(bool closed);

private:
    bool m_closed;
};

#endif // SYMBOLGROUP_H
