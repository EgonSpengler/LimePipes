/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/defines.h>
#include "integratedsymbols.h"
#include "melodynotegraphicbuilder.h"

IntegratedSymbols::IntegratedSymbols(QObject *parent)
    : QObject(parent)
{
}

QStringList IntegratedSymbols::symbols() const
{
    return QStringList();
}

Symbol *IntegratedSymbols::getSymbol(const QString &symbol)
{
    return 0;
}

SymbolGraphicBuilder *IntegratedSymbols::symbolGraphicBuilderForSymbolType(int type)
{
    if (type == LP::MelodyNote)
        return new MelodyNoteGraphicBuilder();

    return 0;
}
