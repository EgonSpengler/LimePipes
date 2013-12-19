/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESSETTINGSPAGE_H
#define SCOREPROPERTIESSETTINGSPAGE_H

#include <QHash>
#include <QWidget>
#include <itemdatatypes.h>
#include <common/settingdefines.h>

namespace Ui {
class ScorePropertiesSettingsPage;
}

class ScorePropertiesWidget;
class ScoreSettings;

class ScorePropertiesSettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ScorePropertiesSettingsPage(Settings::Score::Area area, QWidget *parent = 0);
    explicit ScorePropertiesSettingsPage(QWidget *parent = 0);
    ~ScorePropertiesSettingsPage();

    void setScoreArea(Settings::Score::Area area);
    Settings::Score::Area scoreArea() const;

private:
    void initUi();
    void appendPropertiesWidget(LP::ScoreDataRole dataRole, const QString &text);
    void initPropertiesWidgetsSettings();
    void initPropertiesWidgetWithSettings(LP::ScoreDataRole dataRole, ScorePropertiesWidget *widget);
    QHash<LP::ScoreDataRole, ScorePropertiesWidget*> m_propertiesWidgets;
    Settings::Score::Area m_scoreArea;
    ScoreSettings *m_scoreSettings;
    Ui::ScorePropertiesSettingsPage *ui;
};

#endif // SCOREPROPERTIESSETTINGSPAGE_H
