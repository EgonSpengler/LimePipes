/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
  * @class InstrumentInterface
  * This is the plugin interface for Instruments.
  */

#ifndef INSTRUMENT_INTERFACE_H
#define INSTRUMENT_INTERFACE_H

#include <QtPlugin>

#include <common/datatypes/instrument.h>

class QString;
class Instrument;

class InstrumentInterface {
public:
    virtual ~InstrumentInterface() {}

    virtual int type() const = 0;
    virtual InstrumentMetaData instrumentMetaData() const = 0;
    virtual QString name() const = 0;
};

#define InstrumentInterfaceIID "org.limepipes.LimePipes.InstrumentInterface/0.2"
Q_DECLARE_INTERFACE(InstrumentInterface, InstrumentInterfaceIID)

#endif // INSTRUMENT_INTERFACE_H
