/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PLUGINMANAGERINTERFACE_H
#define PLUGINMANAGERINTERFACE_H

#include <common/graphictypes/MusicFont/musicfont.h>
#include <common/interfaces/symbolinterface.h>
#include <QSharedPointer>

class Symbol;
class Instrument;
class QString;
class QStringList;
class ItemInteraction;
class SymbolGraphicBuilder;

class PluginManagerInterface
{
public:
    PluginManagerInterface() {}
    virtual ~PluginManagerInterface() {}

    virtual QList<SymbolMetaData> symbolMetaDatas() const = 0;
    virtual SymbolMetaData metaDataForSymbol(int type) = 0;
    virtual QVector<int> symbolTypesForInstrument(const QString &instrumentName) const = 0;
    virtual Symbol *symbolForType(int type) = 0;
    virtual QVector<int> additionalDataForSymbolType(int symbolType) = 0;
    virtual SymbolGraphicBuilder *symbolGraphicBuilderForType(int type) = 0;
    virtual ItemInteraction *itemInteractionForType(int type) = 0;

    virtual QStringList instrumentNames() const = 0;
    virtual Instrument *instrumentForName(const QString &name) const = 0;

    virtual MusicFontPtr musicFont() const = 0;
};

typedef QSharedPointer<PluginManagerInterface> PluginManager;

#endif // PLUGINMANAGERINTERFACE_H
