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

#include <QList>

#include <common/datatypes/pitchcontext.h>
#include <common/datahandling/symbolbehavior.h>

#include "ghb_symboltypes.h"
#include "Doubling/doublingbehavior.h"
#include "greathighlandbagpipe.h"

GreatHighlandBagpipe::GreatHighlandBagpipe()
{
    m_metaData.setName(tr("Great Highland Bagpipe"));
    QList<int> supportedSymbols({LP::MelodyNote,
                              LP::Tie,
                              GHB::Doubling});
    m_metaData.setSupportedSymbols(supportedSymbols);
    PitchContext *pitchContext = new PitchContext();

    pitchContext->setStaffType(StaffType::Standard);
    pitchContext->setDefaultClef(ClefType::Treble);

    pitchContext->insertPitch(0, "F");
    pitchContext->insertPitch(1, "E");
    pitchContext->insertPitch(2, "D");
    pitchContext->insertPitch(3, "C");
    pitchContext->insertPitch(4, "B");
    pitchContext->insertPitch(5, "Low A");
    pitchContext->insertPitch(-1, "High G");
    pitchContext->insertPitch(-2, "High A");
    pitchContext->insertPitch(6, "Low G");
    m_metaData.setPitchContext(PitchContextPtr(pitchContext));
}

int GreatHighlandBagpipe::type() const
{
    return LP::GreatHighlandBagpipe;
}

InstrumentMetaData GreatHighlandBagpipe::instrumentMetaData() const
{
    return m_metaData;
}

SymbolGraphicBuilder *GreatHighlandBagpipe::symbolGraphicBuilderForType(int type)
{
    Q_UNUSED(type);
    return 0;
}

QList<int> GreatHighlandBagpipe::symbolTypes() const
{
    return m_metaData.supportedSymbols();
}

SymbolBehavior *GreatHighlandBagpipe::symbolBehaviorForType(int type)
{
    if (type == GHB::Doubling) {
        return new DoublingBehavior;
    }

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

