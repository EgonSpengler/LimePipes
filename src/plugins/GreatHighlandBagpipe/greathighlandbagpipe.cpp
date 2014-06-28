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
    m_symbolTypes << LP::MelodyNote;
    m_symbolTypes << LP::Tie;
    m_symbolTypes << GHB::Doubling;
}

Instrument *GreatHighlandBagpipe::instrument() const
{
    return new GHB_Instrument();
}

SymbolGraphicBuilder *GreatHighlandBagpipe::symbolGraphicBuilderForType(int type)
{
    Q_UNUSED(type);
    return 0;
}

QVector<int> GreatHighlandBagpipe::symbolTypes()
{
    return m_symbolTypes;
}

Symbol *GreatHighlandBagpipe::symbolForType(int type)
{
    QString name = symbolMetaDataForType(type).name();
    if (type == GHB::Doubling)
        return new GHB_Doubling(name);

    return 0;
}

QVector<int> GreatHighlandBagpipe::additionalDataForSymbolType(int symbolType)
{
    return QVector<int>();
}

SymbolMetaData GreatHighlandBagpipe::symbolMetaDataForType(int type)
{
    SymbolMetaData metaData;
    if (type == GHB::Doubling) {
        metaData.setCategory(SymbolCategory::Graphical);
        metaData.setName(tr("Doubling"));
    }

    return metaData;
}
