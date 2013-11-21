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
#include <QSignalMapper>
#include "textpropertyeditwidget.h"
#include "scorepropertiesdialog.h"
#include "ui_scorepropertiesdialog.h"

ScorePropertiesDialog::ScorePropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScorePropertiesDialog)
{
    ui->setupUi(this);

    m_textChangedMapper = new QSignalMapper(this);
    connect(m_textChangedMapper, SIGNAL(mapped(int)),
            this, SLOT(textChanged(int)));

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
    if (!m_textEditWidgets.contains(dataRole)) return;
    TextPropertyEditWidget *editWidget = m_textEditWidgets.value(dataRole);

    if (editWidget->text() != text)
        editWidget->setText(text);
}

void ScorePropertiesDialog::textChanged(int dataRole)
{
    LP::ScoreDataRole scoreRole = static_cast<LP::ScoreDataRole>(dataRole);
    if (!m_textEditWidgets.contains(scoreRole)) return;
    TextPropertyEditWidget *editWidget = m_textEditWidgets.value(scoreRole);

    emit propertyTextChanged(scoreRole, editWidget->text());
}

void ScorePropertiesDialog::fontChanged(int dataRole)
{
    LP::ScoreDataRole scoreRole = static_cast<LP::ScoreDataRole>(dataRole);
    if (!m_textEditWidgets.contains(scoreRole)) return;
    TextPropertyEditWidget *editWidget = m_textEditWidgets.value(scoreRole);

    emit propertyFontChanged(scoreRole, editWidget->font());
}

void ScorePropertiesDialog::colorChanged(int dataRole)
{
    LP::ScoreDataRole scoreRole = static_cast<LP::ScoreDataRole>(dataRole);
    if (!m_textEditWidgets.contains(scoreRole)) return;
    TextPropertyEditWidget *editWidget = m_textEditWidgets.value(scoreRole);

    emit propertyColorChanged(scoreRole, editWidget->color());
}

void ScorePropertiesDialog::addTextEditWidget(int layoutRow, LP::ScoreDataRole dataRole, const QString &text)
{
    TextPropertyEditWidget *textEditWidget = new TextPropertyEditWidget();
    m_textEditWidgets.insert(dataRole, textEditWidget);
    ui->gridLayout->addWidget(new QLabel(text), layoutRow, 0);
    ui->gridLayout->addWidget(textEditWidget, layoutRow, 1);
    connect(textEditWidget, SIGNAL(textChanged(QString)),
            m_textChangedMapper, SLOT(map()));
    m_textChangedMapper->setMapping(textEditWidget, static_cast<int>(dataRole));
}
