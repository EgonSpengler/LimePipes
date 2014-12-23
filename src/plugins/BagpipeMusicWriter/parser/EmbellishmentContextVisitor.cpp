/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDebug>

#include "ast/melodynote.h"
#include "ast/embellishment.h"
#include "EmbellishmentContextVisitor.h"

EmbellishmentContextVisitor::EmbellishmentContextVisitor()
    : m_previousSymbol(Q_NULLPTR)
{
    m_skippingSymbolTypes << T_Bar;
}

EmbellishmentContextVisitor::~EmbellishmentContextVisitor()
{
}

void EmbellishmentContextVisitor::visit(Symbol *symbol)
{
    SymbolType symbolType = symbol->type();

    if (m_skippingSymbolTypes.contains(symbolType)) {
        return;
    }

    if (!m_previousSymbol) {
        m_previousSymbol = symbol;
        return;
    }

    if (m_previousSymbol->type() == T_Melody &&
            symbolType == T_Embellishment) {
        MelodyNote *melodyNote = static_cast<MelodyNote*>(m_previousSymbol);
        Embellishment *embellishment = static_cast<Embellishment*>(symbol);

        if (embellishment == 0 ||
                melodyNote == 0) {
            return;
        }

        embellishment->setPrecedingPitch(melodyNote->pitch());
    }

    if (m_previousSymbol->type() == T_Embellishment &&
            symbolType == T_Melody) {
        Embellishment *embellishment = static_cast<Embellishment*>(m_previousSymbol);
        MelodyNote *melodyNote = static_cast<MelodyNote*>(symbol);

        if (embellishment == 0 ||
                melodyNote == 0) {
            return;
        }

        embellishment->setFollowingPitch(melodyNote->pitch());
    }

    m_previousSymbol = symbol;
}

void EmbellishmentContextVisitor::finishVisit(Part *part)
{
    m_previousSymbol = Q_NULLPTR;
}
