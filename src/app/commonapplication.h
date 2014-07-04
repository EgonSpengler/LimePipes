/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef COMMONAPPLICATION_H
#define COMMONAPPLICATION_H

#include "applicationinterface.h"

class CommonApplication : public ApplicationInterface
{
public:
    CommonApplication();

    // ApplicationInterface interface
    QList<SymbolBehavior> paletteSymbols() const;

public slots:
    void setPaletteSymbols(const QList<SymbolBehavior> &symbols);

private:
    QList<SymbolBehavior> m_paletteSymbols;
};

#endif // COMMONAPPLICATION_H
