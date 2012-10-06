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
#include <pitchcontext.h>

class GreatHighlandBagpipe : public QObject,
                             public InstrumentInterface,
                             public SymbolInterface
{
    Q_OBJECT
    Q_INTERFACES(InstrumentInterface SymbolInterface)

public:
    GreatHighlandBagpipe();

    // Instrument interface
    QString name() const
        { return QString("Great Highland Bagpipe"); }
    InstrumentPtr instrument() const
        { return m_bagpipe; }

    // Symbols interface
    QStringList symbols()
        { return QStringList() << tr("Melody Note")
                               << tr("Bar")
                               << tr("Doubling");
        }
    Symbol *getSymbol(const QString &symbol);

private:
    InstrumentPtr m_bagpipe;
};

#endif // GREATHIGHLANDBAGPIPE_H
