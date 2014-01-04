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

class SettingsObserver : public QObject
{
    Q_OBJECT

public:
    explicit SettingsObserver(QObject *parent = 0);
    explicit SettingsObserver(Settings::Category settingCategory, QObject *parent = 0);
    virtual ~SettingsObserver() {}

    void setSettingsCategory(Settings::Category category);
    Settings::Category settingCategory() const;

    virtual void notify() {}

private:
    Settings::Category m_settingsCategory;
};

#endif // SETTINGSOBSERVER_H
