/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class GreatHighlandBagpipe
  * The Instrument plugin for the Great Highland Bagpipe.
  */

#include "greathighlandbagpipe.h"
#include "ghb_doubling.h"

GreatHighlandBagpipe::GreatHighlandBagpipe()
{
}

Instrument *GreatHighlandBagpipe::instrument() const
{
    return new GHB_Instrument();
}

QStringList GreatHighlandBagpipe::symbolNames() const
{
    return QStringList()    << tr("Melody Note")
                            << tr("Doubling");
}

Symbol *GreatHighlandBagpipe::getSymbolForName(const QString &symbol)
{
    if (symbol == tr("Doubling")) {
        return new GHB_Doubling();
    }
    return new Symbol();
}

SymbolGraphicBuilder *GreatHighlandBagpipe::symbolGraphicBuilderForType(int type)
{
    Q_UNUSED(type);
    return 0;
}

QVector<int> GreatHighlandBagpipe::symbolTypes()
{
    QVector<int> types;
    types << LP::MelodyNote;
    types << GHB::Doubling;

    return types;
}

Symbol *GreatHighlandBagpipe::symbolForType(int type)
{
    if (type == GHB::Doubling)
        return new GHB_Doubling();

    return 0;
}
