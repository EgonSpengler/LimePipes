/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef EMBELLISHMENTCONTEXTVISITOR_H
#define EMBELLISHMENTCONTEXTVISITOR_H

#include "ast/AstVisitorInterface.h"

class EmbellishmentContextVisitor : public AstVisitorInterface
{
public:
    explicit EmbellishmentContextVisitor();
    ~EmbellishmentContextVisitor();

    void visit(Score *score);
    void visit(Tune *tune);
    void visit(Part *part);
    void visit(Symbol *symbol);

    void finishVisit(Score *score);
    void finishVisit(Tune *tune);
    void finishVisit(Part *part);
    void finishVisit(Symbol *symbol);
};

#endif // EMBELLISHMENTCONTEXTVISITOR_H
