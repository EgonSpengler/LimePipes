/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef OBSERVABLESETTINGS_H
#define OBSERVABLESETTINGS_H

#include <QObject>
#include <QList>
#include <QPointer>
#include "settingdefines.h"

class SettingsObserver;

class ObservableSettings : public QObject
{
    Q_OBJECT
    friend class ObservableSettingsTest;

public:
    explicit ObservableSettings(QObject *parent = 0);
    virtual ~ObservableSettings() {}

    static void registerObserver(SettingsObserver *settingsObserver);
    static void unregisterObserver(SettingsObserver *settingsObserver);
    static bool isObserverRegistered(SettingsObserver *settingsObserver);

protected:
    static void notify(Settings::Category category, Settings::Id id);

private:
    static QList<SettingsObserver*> m_settingsObserver;
};

#endif // OBSERVABLESETTINGS_H
