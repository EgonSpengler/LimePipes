/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SYMBOL_H
#define SYMBOL_H

#include "musicitem.h"

class Symbol : public MusicItem
{
public:
    explicit Symbol(MusicItem *parent=0);
    virtual ~Symbol();

    void accept(AstVisitorInterface *visitor);

    bool isGroup() const;
    void setIsGroup(bool isGroup);

    quint8 dots() const;
    void setDots(const quint8 &dots);

private:
    bool m_isGroup;
    quint8 m_dots;
};

#endif // SYMBOL_H
