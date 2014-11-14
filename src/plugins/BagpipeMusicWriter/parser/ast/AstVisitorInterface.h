/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ASTVISITORINTERFACE_H
#define ASTVISITORINTERFACE_H

#include "score.h"
#include "tune.h"
#include "part.h"
#include "symbol.h"

class AstVisitorInterface
{
public:
    explicit AstVisitorInterface() {}
    virtual ~AstVisitorInterface() {}

    virtual void visit(MusicItem *item) {}
    virtual void visit(Score *symbol) {}
    virtual void visit(Tune *tune) {}
    virtual void visit(Part *part) {}
    virtual void visit(Symbol *symbol) {}

    virtual void finishVisit(MusicItem *item) {}
    virtual void finishVisit(Score *symbol) {}
    virtual void finishVisit(Tune *tune) {}
    virtual void finishVisit(Part *part) {}
    virtual void finishVisit(Symbol *symbol) {}
};

#endif // ASTVISITORINTERFACE_H
