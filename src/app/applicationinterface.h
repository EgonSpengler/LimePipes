/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef APPLICATIONINTERFACE_H
#define APPLICATIONINTERFACE_H

#include <QList>
#include <common/datahandling/symbolbehavior.h>

class ApplicationInterface
{
public:
    ApplicationInterface() {}
    virtual ~ApplicationInterface() {}

    /*!
     * \brief paletteSymbols Returns the symbol(s) that are currently selected in the
     *        symbol palette.
     */
    virtual QList<SymbolBehavior> paletteSymbols() const = 0;
};

typedef QSharedPointer<ApplicationInterface> Application;

#endif // APPLICATIONINTERFACE_H
