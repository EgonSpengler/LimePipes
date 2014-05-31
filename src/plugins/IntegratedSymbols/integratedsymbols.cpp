/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/defines.h>
#include <symbols/melodynote.h>
#include <MelodyNote/melodynoteinteraction.h>
#include "integratedsymbols.h"
#include "melodynotegraphicbuilder.h"

IntegratedSymbols::IntegratedSymbols(QObject *parent)
    : QObject(parent)
{
}

SymbolGraphicBuilder *IntegratedSymbols::symbolGraphicBuilderForType(int type)
{
    if (type == LP::MelodyNote)
        return new MelodyNoteGraphicBuilder();

    return 0;
}

QVector<int> IntegratedSymbols::symbolTypes()
{
    QVector<int> types;
    types << LP::MelodyNote;

    return types;
}

Symbol *IntegratedSymbols::symbolForType(int type)
{
    if (type == LP::MelodyNote)
        return new MelodyNote();

    return 0;
}

ItemInteraction *IntegratedSymbols::itemInteractionForType(int type)
{
    if (type == LP::MelodyNote) {
        return new MelodyNoteInteraction();
    }

    return SymbolInterface::itemInteractionForType(type);
}
