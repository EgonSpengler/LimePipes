/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef EMBELLISHMENTCONTEXTVISITOR_H
#define EMBELLISHMENTCONTEXTVISITOR_H

#include <QList>

#include "ast/AstDefines.h"
#include "ast/AstVisitorInterface.h"

/*!
 * \brief The EmbellishmentContextVisitor class
 * Adds preceeding pitch and following pitch to embellishment symbols.
 */
class EmbellishmentContextVisitor : public AstVisitorInterface
{
public:
    explicit EmbellishmentContextVisitor();
    ~EmbellishmentContextVisitor();

    void visit(Score *) {}
    void visit(Tune *) {}
    void visit(Part *) {}
    void visit(Symbol *symbol);

    void finishVisit(Score *) {}
    void finishVisit(Tune *) {}
    void finishVisit(Part *part);
    void finishVisit(Symbol *) {}

private:
    Symbol *m_previousSymbol;
    QList<SymbolType> m_skippingSymbolTypes; //!< Skipping types of symbols, which are valid
                                             ///  between embellishments and melody notes
};

#endif // EMBELLISHMENTCONTEXTVISITOR_H
