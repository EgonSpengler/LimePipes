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
    SymbolMetaData symbolMetaDataForType(int type);
    Symbol *symbolForType(int type);
    QList<int> symbolTypes() const;
    SymbolGraphicBuilder *symbolGraphicBuilderForType(int type);
    ItemInteraction *itemInteractionForType(int type);
    QVector<int> additionalDataForSymbolType(int symbolType);

private:
    QList<int> m_symbolTypes;
};

#endif // INTEGRATEDSYMBOLS_H
