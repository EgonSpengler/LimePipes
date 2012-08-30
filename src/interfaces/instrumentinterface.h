/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INSTRUMENT_INTERFACE_H
#define INSTRUMENT_INTERFACE_H

#include <QtPlugin>
#include <instrument_ids.h>

class QString;

class InstrumentInterface {
public:
    virtual ~InstrumentInterface() {}
    virtual QString name() const = 0;
    virtual LP::InstrumentId instrumentId() const = 0;
};

Q_DECLARE_INTERFACE(InstrumentInterface,
                    "org.limepipes.LimePipes.InstrumentInterface/0.1")

#endif // INSTRUMENT_INTERFACE_H
