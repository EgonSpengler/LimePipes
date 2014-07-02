/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <common/itemdataroles.h>
#include <common/datatypes/instrument.h>
#include <common/datahandling/measurebehavior.h>

#include <symbol.h>
#include "measure.h"

Measure::Measure(MusicItem *parent)
{
    initItem();
}

Measure::Measure(const PluginManager &pluginManager, MusicItem *parent)
    : MusicItem(MusicItem::MeasureType, MusicItem::SymbolType, parent),
      m_pluginManager(pluginManager)
{
    initItem();
}

void Measure::initItem()
{
    ItemBehavior *behavior = new MeasureBehavior;
    setItemBehavior(behavior);
}

bool Measure::itemSupportsWritingOfData(int role) const
{
    if (LP::allMeasureDataRoles.contains(static_cast<LP::MeasureDataRole>(role)))
        return true;

    return false;
}

void Measure::writeItemDataToXmlStream(QXmlStreamWriter *writer)
{
}

void Measure::readCurrentElementFromXmlStream(QXmlStreamReader *reader)
{
}

bool Measure::okToInsertChild(const MusicItem *item, int row)
{
    Q_UNUSED(row);

    MusicItem *part = parent();
    if (!part) return false;

    MusicItem *tune = part->parent();
    if (!tune) return false;

    int instrumentType = tune->data(LP::TuneInstrument).toInt();
    if (instrumentType == LP::NoInstrument)
        return false;

    const Symbol *symbol = static_cast<const Symbol*>(item);
    if (!symbol) return false;

    if (m_pluginManager.isNull()) {
        qWarning() << "Measure: Plugin manager is null";
        return false;
    }

    InstrumentMetaData instrumentMeta = m_pluginManager->instrumentMetaData(instrumentType);
    int symbolType = symbol->symbolType();
    if (symbolType == LP::NoSymbolType) {
        qWarning() << "Measure: Can't insert symbol with no type";
        return false;
    }

    return instrumentMeta.supportsSymbol(symbolType);
}

PluginManager Measure::pluginManager() const
{
    return m_pluginManager;
}

void Measure::setPluginManager(const PluginManager &pluginManager)
{
    m_pluginManager = pluginManager;
}
