/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TESTSETTINGSOBSERVER_H
#define TESTSETTINGSOBSERVER_H

#include <common/settingsobserver.h>

class TestSettingsObserver : public SettingsObserver
{
    Q_OBJECT

public:
    explicit TestSettingsObserver(QObject *parent = 0);

    void notify();

signals:
    void notifyCalled();
};

#endif // TESTSETTINGSOBSERVER_H
