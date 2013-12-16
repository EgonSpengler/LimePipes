/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "scorepropertiessettingspage.h"
#include "scorepropertieswidget.h"
#include "ui_scorepropertiessettingspage.h"

ScorePropertiesSettingsPage::ScorePropertiesSettingsPage(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::ScorePropertiesSettingsPage)
{
    ui->setupUi(this);

    appendPropertiesWidget(LP::ScoreTitle, tr("Title"));
    appendPropertiesWidget(LP::ScoreType, tr("Type"));
    appendPropertiesWidget(LP::ScoreComposer, tr("Composer"));
    appendPropertiesWidget(LP::ScoreArranger, tr("Arranger"));
    appendPropertiesWidget(LP::ScoreCopyright, tr("Copyright"));
    appendPropertiesWidget(LP::ScoreYear, tr("Year"));
}

void ScorePropertiesSettingsPage::appendPropertiesWidget(LP::ScoreDataRole dataRole, const QString& text)
{
    ScorePropertiesWidget *propertyWidget = new ScorePropertiesWidget();
    propertyWidget->setText(text);
    propertiesWidgets.insert(dataRole, propertyWidget);
    ui->verticalLayout->addWidget(propertyWidget);
}

ScorePropertiesSettingsPage::~ScorePropertiesSettingsPage()
{
    delete ui;
}
