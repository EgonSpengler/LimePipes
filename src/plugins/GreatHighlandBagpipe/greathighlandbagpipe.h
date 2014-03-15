/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GREATHIGHLANDBAGPIPE_H
#define GREATHIGHLANDBAGPIPE_H

#include <QObject>
#include <QStringList>
#include "ghb_instrument.h"
#include <common/interfaces/instrumentinterface.h>
#include <common/interfaces/symbolinterface.h>

class GreatHighlandBagpipe :    public QObject,
                                public InstrumentInterface,
                                public SymbolInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID InstrumentInterfaceIID FILE "greathighlandbagpipe.json")
    Q_INTERFACES(InstrumentInterface SymbolInterface)

public:
    GreatHighlandBagpipe();

    // Instrument interface
    QString name() const { return QString("Great Highland Bagpipe"); }
    Instrument *instrument() const;

    // Symbols interface
    QStringList symbolNames() const;
    Symbol *getSymbolForName(const QString &symbol);

    QVector<int> symbolTypes();
    SymbolGraphicBuilder *symbolGraphicBuilderForType(int type);
};

#endif // GREATHIGHLANDBAGPIPE_H
