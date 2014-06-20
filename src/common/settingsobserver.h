/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SETTINGSOBSERVER_H
#define SETTINGSOBSERVER_H

#include <QObject>
#include "settingdefines.h"

class SettingsObserver
{
public:
    explicit SettingsObserver();
    explicit SettingsObserver(Settings::Category settingCategory);
    virtual ~SettingsObserver() {}

    Settings::Category settingCategory() const;

    virtual void notify(Settings::Id id) { Q_UNUSED(id); }

protected:
    void setSettingsCategory(Settings::Category category);

private:
    Settings::Category m_settingsCategory;
};

#endif // SETTINGSOBSERVER_H
