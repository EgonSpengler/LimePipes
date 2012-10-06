/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "instrument.h"

/*! @class Instrument
    @brief A class which provides a Instrument.
*/

Instrument::Instrument(const Instrument &other)
{
    this->m_type = other.m_type;
    this->m_name = other.m_name;
    this->m_pitchContext = other.m_pitchContext;
}
