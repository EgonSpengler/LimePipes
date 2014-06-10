/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/defines.h>

#include "symbols/melodynote.h"
#include "symbols/tie.h"

#include "MelodyNote/melodynoteinteraction.h"
#include "MelodyNote/melodynotegraphicbuilder.h"

#include "Tie/tiegraphicbuilder.h"
#include "integratedsymbols.h"

IntegratedSymbols::IntegratedSymbols(QObject *parent)
    : QObject(parent)
{
    m_symbolTypes << LP::MelodyNote;
    m_symbolTypes << LP::Tie;
}

SymbolGraphicBuilder *IntegratedSymbols::symbolGraphicBuilderForType(int type)
{
    if (type == LP::MelodyNote)
        return new MelodyNoteGraphicBuilder();
    if (type == LP::Tie)
        return new TieGraphicBuilder();

    return 0;
}

QVector<int> IntegratedSymbols::symbolTypes()
{
    return m_symbolTypes;
}

Symbol *IntegratedSymbols::symbolForType(int type)
{
    switch (type) {
    case LP::MelodyNote:
        return new MelodyNote();
    case LP::Tie:
        return new Tie();
    }

    return 0;
}

ItemInteraction *IntegratedSymbols::itemInteractionForType(int type)
{
    if (type == LP::MelodyNote) {
        return new MelodyNoteInteraction();
    }

    return SymbolInterface::itemInteractionForType(type);
}

QVector<int> IntegratedSymbols::additionalDataForSymbolType(int symbolType)
{
    if (symbolType == LP::MelodyNote) {
        return QVector<int>({LP::MelodyNoteDots});
    }

    return QVector<int>();
}
