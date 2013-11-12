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
#include "interfaceglobals.h"
#include <symbol.h>

class QString;
class QStringList;

class SymbolInterface {
public:
    virtual ~SymbolInterface() {}
    virtual QStringList symbols() const = 0;
    virtual Symbol *getSymbol( const QString &symbol ) = 0;
};

#define SymbolInterfaceIID "org.limepipes.LimePipes.SymbolInterface/0.2"
Q_DECLARE_INTERFACE(SymbolInterface, SymbolInterfaceIID)

#endif // SYMBOLINTERFACE_H
