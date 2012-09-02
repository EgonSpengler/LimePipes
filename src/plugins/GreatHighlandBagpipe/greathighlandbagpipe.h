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
#include <QObject>
#include <QString>
#include <greathighlandbagpipeinstrument.h>

class GreatHighlandBagpipe : public QObject,
                             public InstrumentInterface
{
    Q_OBJECT
    Q_INTERFACES(InstrumentInterface)

public:
    QString name() const
        { return QString("Great Highland Bagpipe"); }
    Instrument *instrument() const
        { return new GreatHighlandBagpipeInstrument(); }
};

#endif // GREATHIGHLANDBAGPIPE_H
