/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICMODELTESTPLUGIN_GLOBAL_H
#define MUSICMODELTESTPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MUSICMODELTESTPLUGIN_LIBRARY)
#  define MUSICMODELTESTPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MUSICMODELTESTPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MUSICMODELTESTPLUGIN_GLOBAL_H
