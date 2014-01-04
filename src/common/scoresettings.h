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
#include "observablesettings.h"

class QSettings;

class ScoreSettings : public ObservableSettings
{
    friend class ScoreSettingsTest;

public:
    explicit ScoreSettings(Settings::Score::Area scoreArea, LP::ScoreDataRole dataRole, QObject *parent = 0);
    explicit ScoreSettings(QObject *parent = 0);

    QVariant value(Settings::Score::Appearance appearance);
    QVariant value(Settings::Score::Area area, LP::ScoreDataRole dataRole, Settings::Score::Appearance appearance);

    void setValue(Settings::Score::Appearance appearance, const QVariant& value);
    void setValue(Settings::Score::Area area, LP::ScoreDataRole dataRole, Settings::Score::Appearance appearance, const QVariant& value);

    void remove(Settings::Score::Appearance appearance);
    void remove(Settings::Score::Area area, LP::ScoreDataRole dataRole, Settings::Score::Appearance appearance);

    Settings::Score::Area scoreArea() const;
    void setScoreArea(Settings::Score::Area scoreArea);

    LP::ScoreDataRole dataRole() const;
    void setDataRole(LP::ScoreDataRole dataRole);

    void clear();
    void sync();
    QString fileName();

private:
    static QString getKey(Settings::Score::Area area, LP::ScoreDataRole dataRole, Settings::Score::Appearance appearance);
    static QVariant defaultValue(const QString& key);
    static QHash <QString, QVariant> m_defaultValues;
    static QHash<QString, QVariant> initDefaultValues();
    static QString alignmentToString(Settings::TextAlignment alignment);
    static Settings::TextAlignment alignmentFromString(const QString& alignment);

    Settings::Score::Area m_scoreArea;
    LP::ScoreDataRole m_dataRole;
    QSettings *m_settings;
};

#endif // SCORESETTINGS_H
