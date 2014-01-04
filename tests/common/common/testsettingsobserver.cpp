/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "testsettingsobserver.h"

TestSettingsObserver::TestSettingsObserver(QObject *parent)
    : SettingsObserver(parent)
{
}

void TestSettingsObserver::notify()
{
    emit notifyCalled();
}
