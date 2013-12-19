/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QFont>
#include "scorepropertiessettingspage.h"
#include "scorepropertieswidget.h"
#include <common/scoresettings.h>
#include "ui_scorepropertiessettingspage.h"

using namespace Settings::Score;

ScorePropertiesSettingsPage::ScorePropertiesSettingsPage(Area area, QWidget *parent)
    : QWidget(parent),
      m_scoreArea(area),
      m_scoreSettings(0),
      ui(new Ui::ScorePropertiesSettingsPage)
{
    ui->setupUi(this);

    m_scoreSettings = new ScoreSettings(this);
    m_scoreSettings->setScoreArea(area);

    initUi();
    initPropertiesWidgetsSettings();
}

ScorePropertiesSettingsPage::ScorePropertiesSettingsPage(QWidget *parent)
    : QWidget(parent),
      m_scoreArea(Header),
      ui(new Ui::ScorePropertiesSettingsPage)
{
    ui->setupUi(this);

    m_scoreSettings = new ScoreSettings(this);

    initUi();
    initPropertiesWidgetsSettings();
}

void ScorePropertiesSettingsPage::initUi()
{
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
    m_propertiesWidgets.insert(dataRole, propertyWidget);
    ui->verticalLayout->addWidget(propertyWidget);
}

void ScorePropertiesSettingsPage::initPropertiesWidgetsSettings()
{
    foreach (LP::ScoreDataRole dataRole, m_propertiesWidgets.keys()) {
        initPropertiesWidgetWithSettings(dataRole, m_propertiesWidgets.value(dataRole));
    }
}

void ScorePropertiesSettingsPage::initPropertiesWidgetWithSettings(LP::ScoreDataRole dataRole, ScorePropertiesWidget *widget)
{
    m_scoreSettings->setScoreArea(m_scoreArea);
    m_scoreSettings->setDataRole(dataRole);

    widget->setWidgetEnabled(m_scoreSettings->value(Enabled).toBool());
    widget->setFont(m_scoreSettings->value(Font).value<QFont>());
    widget->setColor(m_scoreSettings->value(Color).value<QColor>());
    widget->setAlignment(m_scoreSettings->value(Alignment).value<Settings::TextAlignment>());
    widget->setRow(m_scoreSettings->value(Row).toInt());
}

ScorePropertiesSettingsPage::~ScorePropertiesSettingsPage()
{
    delete ui;
}

void ScorePropertiesSettingsPage::setScoreArea(Area area)
{
    m_scoreArea = area;
    m_scoreSettings->setScoreArea(area);
    initPropertiesWidgetsSettings();
}

Area ScorePropertiesSettingsPage::scoreArea() const
{
    return m_scoreArea;
}
