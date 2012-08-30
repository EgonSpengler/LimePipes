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
#include <instrumentinterface.h>
#include <QString>

class GreatHighlandBagpipe : public QObject,
                             public InstrumentInterface
{
    Q_OBJECT
    Q_INTERFACES(InstrumentInterface)

public:
    QString name() const
        { return QString("Great Highland Bagpipe"); }
    LP::InstrumentId instrumentId() const
        { return LP::GreatHighlandBagpipe; }
};

#endif // GREATHIGHLANDBAGPIPE_H
