/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PLUGINMANAGERINTERFACE_H
#define PLUGINMANAGERINTERFACE_H

#include <common/graphictypes/SMuFL/smufl.h>
#include <QSharedPointer>

class Symbol;
class Instrument;
class QString;
class QStringList;
class SymbolGraphicBuilder;

class PluginManagerInterface
{
public:
    PluginManagerInterface() {}
    virtual ~PluginManagerInterface() {}

    // Deprecated. Is used by import/export from LimePipes xml files
    virtual QStringList symbolNamesForInstrument(const QString &instrumentName) const = 0;
    virtual Symbol *symbolForName(const QString &instrumentName, const QString &symbolName) const = 0;
    // End of deprecated

    virtual QVector<int> symbolTypesForInstrument(const QString &instrumentName) const = 0;
    virtual Symbol *symbolForType(int type) = 0;
    virtual SymbolGraphicBuilder *symbolGraphicBuilderForType(int type) = 0;

    virtual QStringList instrumentNames() const = 0;
    virtual Instrument *instrumentForName(const QString &name) const = 0;

    virtual SMuFLPtr smufl() const = 0;
};

typedef QSharedPointer<PluginManagerInterface> PluginManager;

#endif // PLUGINMANAGERINTERFACE_H
