/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "instrument.h"

/*! @class Instrument
    @brief A class which provides a default implementation of the InstrumentInterface.

    This class is an implementation of the InstrumentInterface. This class is required because
    InstrumentInterface can't be declared as a QMetaType. This is needed to store objects as a
    QVariant.
    A specific implementation of an Instrument can be set with setInstrument. After this is set,
    all InstrumentInterface calls will be redirected to that implementation.
    The default constructor uses a Great Highland Bagpipe as instrument.
*/
