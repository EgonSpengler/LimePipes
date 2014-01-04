/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "settingsobserver.h"

using namespace Settings;

SettingsObserver::SettingsObserver(QObject *parent)
    :
      m_settingsCategory(Category::NoCategory)
{
}

SettingsObserver::SettingsObserver(Settings::Category settingCategory, QObject *parent)
    :
      m_settingsCategory(settingCategory)
{
}

void SettingsObserver::setSettingsCategory(Settings::Category category)
{
    m_settingsCategory = category;
}

Settings::Category SettingsObserver::settingCategory() const
{
    return m_settingsCategory;
}
