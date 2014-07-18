/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/defines.h>
#include <common/datahandling/symbolbehavior.h>
#include <QFile>

#include "MelodyNote/melodynotebehavior.h"
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

QList<int> IntegratedSymbols::symbolTypes() const
{
    return m_symbolTypes;
}

SymbolBehavior *IntegratedSymbols::symbolBehaviorForType(int type)
{
    if (type == LP::MelodyNote) {
        return new MelodyNoteBehavior;
    }

    SymbolBehavior *behavior = new SymbolBehavior;
    behavior->setSymbolType(type);

    if (type == LP::Tie) {
        behavior->setSupportedData(QList<int>({LP::SymbolSpanType,
                                               LP::SymbolSpanBuddy}));
    }

    return behavior;
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

SymbolMetaData IntegratedSymbols::symbolMetaDataForType(int type)
{
    SymbolMetaData metaData;
    if (type == LP::MelodyNote) {
        metaData.setCategory(SymbolCategory::Graphical);
        metaData.setName(tr("Melody Note"));
        metaData.setIconPixmap(QPixmap(":/IntegratedSymbols/melodynote.png"));
    }

    if (type == LP::Tie) {
        metaData.setCategory(SymbolCategory::Spanning);
        metaData.setName(tr("Tie"));
        metaData.setIconPixmap(QPixmap(":/IntegratedSymbols/tie.png"));
    }

    return metaData;
}

