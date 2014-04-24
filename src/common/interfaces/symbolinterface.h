/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class SymbolInterface
  * This is the plugin interface for Symbols.
  */

#ifndef SYMBOLINTERFACE_H
#define SYMBOLINTERFACE_H

#include <QtPlugin>
#include <QVector>
#include <symbol.h>

class QString;
class QStringList;
class SymbolGraphicBuilder;

class SymbolInterface {
public:

    // Deprecated. Is used by import/export from LimePipes xml files
    virtual QStringList symbolNames() const = 0;
    virtual Symbol *getSymbolForName( const QString &symbol ) = 0;
    // End of deprecated

    virtual ~SymbolInterface() {}
    virtual Symbol *symbolForType(int type) = 0;

    virtual QVector<int> symbolTypes() = 0;
    virtual SymbolGraphicBuilder *symbolGraphicBuilderForType(int type) = 0;
};

#define SymbolInterfaceIID "org.limepipes.LimePipes.SymbolInterface/0.2"
Q_DECLARE_INTERFACE(SymbolInterface, SymbolInterfaceIID)

#endif // SYMBOLINTERFACE_H
