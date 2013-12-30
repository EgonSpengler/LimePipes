/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QFontDialog>
#include <QColorDialog>
#include <QLabel>
#include "textpropertyeditwidget.h"
#include "scorepropertiesdialog.h"
#include "ui_scorepropertiesdialog.h"

ScorePropertiesDialog::ScorePropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScorePropertiesDialog)
{
    qRegisterMetaType<LP::ScoreDataRole>("LP::ScoreDataRole");

    ui->setupUi(this);

    addTextEditWidget(0, LP::ScoreTitle, tr("Title"));
    addTextEditWidget(1, LP::ScoreType, tr("Type"));
    addTextEditWidget(2, LP::ScoreComposer, tr("Composer"));
    addTextEditWidget(3, LP::ScoreArranger, tr("Arranger"));
    addTextEditWidget(4, LP::ScoreYear, tr("Year"));
    addTextEditWidget(5, LP::ScoreCopyright, tr("Copyright"));
}

ScorePropertiesDialog::~ScorePropertiesDialog()
{
    delete ui;
}

void ScorePropertiesDialog::setPropertyText(int dataRole, const QString &text)
{
    TextPropertyEditWidget *editWidget = textEditWidgetForRole(dataRole);
    if (!editWidget)
        return;

    editWidget->setText(text);
}

QString ScorePropertiesDialog::propertyText(int dataRole) const
{
    TextPropertyEditWidget *editWidget = textEditWidgetForRole(dataRole);
    if (!editWidget)
        return QString();

    return editWidget->text();
}

TextPropertyEditWidget *ScorePropertiesDialog::textEditWidgetForRole(int dataRole) const
{
    if (!m_textEditWidgets.contains(dataRole))
        return 0;

    return m_textEditWidgets.value(dataRole);
}

void ScorePropertiesDialog::addTextEditWidget(int layoutRow, LP::ScoreDataRole dataRole, const QString &text)
{
    TextPropertyEditWidget *textEditWidget = new TextPropertyEditWidget();
    m_textEditWidgets.insert(dataRole, textEditWidget);
    ui->gridLayout->addWidget(new QLabel(text), layoutRow, 0);
    ui->gridLayout->addWidget(textEditWidget, layoutRow, 1);
    connect(textEditWidget, &TextPropertyEditWidget::textChanged,
            [this, dataRole, textEditWidget] {
        emit propertyTextChanged(dataRole, textEditWidget->text());
    } );
}
