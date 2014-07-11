/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PLUGINMANAGERINTERFACE_H
#define PLUGINMANAGERINTERFACE_H

#include <QSharedPointer>

#include <common/graphictypes/MusicFont/musicfont.h>
#include <common/interfaces/symbolinterface.h>
#include <common/interfaces/instrumentinterface.h>

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
    virtual SymbolMetaData symbolMetaData(int type) const = 0;

    virtual QList<InstrumentMetaData> instrumentMetaDatas() const = 0;
    virtual InstrumentMetaData instrumentMetaData(int type) const = 0;
    // TODO Overloaded method with instrument name parameter maybe useless (translation)
    virtual InstrumentMetaData instrumentMetaData(const QString &instrumentName) const = 0;

    virtual SymbolBehavior *symbolBehaviorForType(int type) = 0;
//    virtual Symbol *symbolForType(int type) = 0;
    virtual QVector<int> additionalDataForSymbolType(int symbolType) = 0;
    virtual SymbolGraphicBuilder *symbolGraphicBuilderForType(int type) = 0;
    virtual ItemInteraction *itemInteractionForType(int type) = 0;

    virtual QStringList instrumentNames() const = 0;
    virtual QList<int> instrumentTypes() const = 0;

    virtual MusicFontPtr musicFont() const = 0;
};

typedef QSharedPointer<PluginManagerInterface> PluginManager;

#endif // PLUGINMANAGERINTERFACE_H
