/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INTEGRATEDSYMBOLS_H
#define INTEGRATEDSYMBOLS_H

#include <QObject>
#include <QStringList>
#include <common/interfaces/symbolinterface.h>

class IntegratedSymbols : public QObject,
                          public SymbolInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID SymbolInterfaceIID FILE "integratedsymbols.json")
    Q_INTERFACES(SymbolInterface)

public:
    explicit IntegratedSymbols(QObject *parent = 0);

    // SymbolInterface interface
public:
    QStringList symbolNames() const;
    Symbol *getSymbolForName(const QString &symbol);
    Symbol *symbolForType(int type);

    QVector<int> symbolTypes();
    SymbolGraphicBuilder *symbolGraphicBuilderForType(int type);
    ItemInteraction *itemInteractionForType(int type);
};

#endif // INTEGRATEDSYMBOLS_H
