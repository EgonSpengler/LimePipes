/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <QMetaType>

enum class StaffType
{
    None,     //!< No lines, e.g. for vocals
    Standard, //!< The standard 5 line staff
};

Q_DECLARE_METATYPE(StaffType)

#endif // DEFINES_H
