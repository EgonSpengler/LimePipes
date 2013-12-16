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

namespace Ui {
class ScorePropertiesSettingsPage;
}

class ScorePropertiesWidget;

class ScorePropertiesSettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ScorePropertiesSettingsPage(QWidget *parent = 0);
    ~ScorePropertiesSettingsPage();

private:
    void appendPropertiesWidget(LP::ScoreDataRole dataRole, const QString &text);
    QHash<LP::ScoreDataRole, ScorePropertiesWidget*> propertiesWidgets;
    Ui::ScorePropertiesSettingsPage *ui;
};

#endif // SCOREPROPERTIESSETTINGSPAGE_H
