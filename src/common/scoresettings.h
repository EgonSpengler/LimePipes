/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCORESETTINGS_H
#define SCORESETTINGS_H

#include <QObject>
#include <QHash>
#include <QString>
#include <QVariant>
#include "settingdefines.h"

class QSettings;

class ScoreSettings : public QObject
{
public:
    explicit ScoreSettings(QObject *parent = 0);

    QVariant value(Settings::Score::Area area, LP::ScoreDataRole dataRole, Settings::Score::Appearance appearance);

private:
    static QString getKey(Settings::Score::Area area, LP::ScoreDataRole dataRole, Settings::Score::Appearance appearance);
    static QVariant defaultValue(const QString& key);
    QSettings *m_settings;
    static QHash <QString, QVariant> m_defaultValues;
    static QHash<QString, QVariant> initDefaultValues();
};

#endif // SCORESETTINGS_H
