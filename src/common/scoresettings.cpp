/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QFont>
#include <QSettings>
#include "scoresettings.h"

using namespace Settings::Score;

namespace
{
////////////
///  Keys
///////////

// Header and Footer
QString HeaderSettingsKey("score header");
QString FooterSettingsKey("score footer");

// Data type
QString TitleKey("title");
QString ComposerKey("composer");
QString ArrangerKey("arranger");
QString YearKey("year");
QString CopyrightKey("copyright");
QString TypeKey("type");

// Style
QString EnabledKey("enabled");

QString FontKey("font");
QString ColorKey("color");

// Position
QString RowKey("row");
QString AlignmentKey("alignment");

}

QHash <QString, QVariant> ScoreSettings::m_defaultValues = ScoreSettings::initDefaultValues();

QHash<QString, QVariant> ScoreSettings::initDefaultValues()
{
    using namespace Settings;

    QHash<QString, QVariant> defaultValues;
    defaultValues.insert(getKey(Header, LP::ScoreType, Enabled), true);
    defaultValues.insert(getKey(Header, LP::ScoreType, Row), 1);
    defaultValues.insert(getKey(Header, LP::ScoreType, Alignment),
                    QVariant::fromValue<TextAlignment>(TextAlignment::Left));

    defaultValues.insert(getKey(Header, LP::ScoreTitle, Enabled), true);
    defaultValues.insert(getKey(Header, LP::ScoreTitle, Row), 1);
    defaultValues.insert(getKey(Header, LP::ScoreTitle, Alignment),
                    QVariant::fromValue<TextAlignment>(TextAlignment::Center));
    defaultValues.insert(getKey(Header, LP::ScoreTitle, Font), QFont("Arial", 18, QFont::Bold));


    defaultValues.insert(getKey(Header, LP::ScoreComposer, Enabled), true);
    defaultValues.insert(getKey(Header, LP::ScoreComposer, Row), 1);
    defaultValues.insert(getKey(Header, LP::ScoreComposer, Alignment),
                         QVariant::fromValue<TextAlignment>(TextAlignment::Right));

    defaultValues.insert(getKey(Header, LP::ScoreArranger, Enabled), true);
    defaultValues.insert(getKey(Header, LP::ScoreArranger, Row), 2);
    defaultValues.insert(getKey(Header, LP::ScoreArranger, Alignment),
                         QVariant::fromValue<TextAlignment>(TextAlignment::Right));

    return defaultValues;
}

ScoreSettings::ScoreSettings(Area scoreArea, LP::ScoreDataRole dataRole, QObject *parent)
    : QObject(parent),
      m_scoreArea(scoreArea),
      m_dataRole(dataRole)
{
    m_settings = new QSettings(this);
}

ScoreSettings::ScoreSettings(QObject *parent)
    : QObject(parent)
{
    m_settings = new QSettings(this);
}

QVariant ScoreSettings::value(Appearance appearance)
{
    return value(m_scoreArea, m_dataRole, appearance);
}

QVariant ScoreSettings::value(Area area, LP::ScoreDataRole dataRole, Appearance appearance)
{
    QString valueKey(getKey(area, dataRole, appearance));
    return m_settings->value(valueKey, defaultValue(valueKey));
}

Area ScoreSettings::scoreArea() const
{
    return m_scoreArea;
}

void ScoreSettings::setScoreArea(Area scoreArea)
{
    m_scoreArea = scoreArea;
}

LP::ScoreDataRole ScoreSettings::dataRole() const
{
    return m_dataRole;
}

void ScoreSettings::setDataRole(LP::ScoreDataRole dataRole)
{
    m_dataRole = dataRole;
}

QString ScoreSettings::getKey(Area area, LP::ScoreDataRole dataRole, Appearance appearance)
{
    QString key;
    switch (area) {
        case Header:
            key += HeaderSettingsKey;
            break;
        case Footer:
            key += FooterSettingsKey;
    }

    key += "/";

    switch (dataRole) {
    case LP::ScoreTitle: {
        key += TitleKey;
        break;
    }
    case LP::ScoreArranger: {
        key += ArrangerKey;
        break;
    }
    case LP::ScoreComposer: {
        key += ComposerKey;
        break;
    }
    case LP::ScoreCopyright: {
        key += CopyrightKey;
        break;
    }
    case LP::ScoreType: {
        key += TypeKey;
        break;
    }
    case LP::ScoreYear: {
        key += YearKey;
        break;
    }
    }

    key += "/";

    switch (appearance) {
    case Enabled: {
        key += EnabledKey;
        break;
    }
    case Font: {
        key += FontKey;
        break;
    }
    case Color: {
        key += ColorKey;
        break;
    }
    case Row: {
        key += RowKey;
        break;
    }
    case Alignment: {
        key += AlignmentKey;
        break;
    }
    }

    return key;
}

QVariant ScoreSettings::defaultValue(const QString &key)
{
    return m_defaultValues.value(key, QVariant());
}
