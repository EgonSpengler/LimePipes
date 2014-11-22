/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include "AstDefines.h"
#include "musicitem.h"

class Symbol : public MusicItem
{
public:
    explicit Symbol(SymbolType type, MusicItem *parent=0);
    virtual ~Symbol();

    void accept(AstVisitorInterface *visitor);

    bool isGroup() const;
    void setIsGroup(bool isGroup);

    quint8 dots() const;
    void setDots(const quint8 &dots);

    SymbolType type() const;
    void setType(const SymbolType &type);

private:
    bool m_isGroup;
    SymbolType m_type;
};

#endif // SYMBOL_H
