/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "settingsobserver.h"
#include "observablesettings.h"

QList<SettingsObserver*> ObservableSettings::m_settingsObserver;

using namespace Settings;

ObservableSettings::ObservableSettings(QObject *parent)
    : QObject(parent)
{
}

void ObservableSettings::registerObserver(SettingsObserver *settingsObserver)
{
    if (settingsObserver->settingCategory() == Category::NoCategory) {
        qWarning("Settings observer with not settings category can't be registered");
        return;
    }

    m_settingsObserver.append(settingsObserver);
}

void ObservableSettings::unregisterObserver(SettingsObserver *settingsObserver)
{
    m_settingsObserver.removeAll(settingsObserver);
}

void ObservableSettings::notify(Settings::Category category)
{
    foreach (SettingsObserver *settingsObserver, m_settingsObserver) {
        if (settingsObserver->settingCategory() == category) {
            settingsObserver->notify();
        }
    }
}

bool ObservableSettings::isObserverRegistered(SettingsObserver *settingsObserver)
{
    return m_settingsObserver.contains(settingsObserver);
}
