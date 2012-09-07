/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GREATHIGHLANDBAGPIPE_H
#define GREATHIGHLANDBAGPIPE_H

#include <instrumentinterface.h>
#include <symbolinterface.h>
#include <QObject>
#include <QString>
#include <QStringList>
#include <ghb_instrument.h>

class GreatHighlandBagpipe : public QObject,
                             public InstrumentInterface,
                             public SymbolInterface
{
    Q_OBJECT
    Q_INTERFACES(InstrumentInterface SymbolInterface)

public:
    // Instrument interface
    QString name() const
        { return QString("Great Highland Bagpipe"); }
    Instrument *instrument() const
        { return new GHB_Instrument(); }

    // Symbols interface
    QStringList symbols()
        { return QStringList() << tr("Melody Note")
                               << tr("Bar")
                               << tr("Doubling");
        }
    Symbol *getSymbol(const QString &symbol);
};

#endif // GREATHIGHLANDBAGPIPE_H
