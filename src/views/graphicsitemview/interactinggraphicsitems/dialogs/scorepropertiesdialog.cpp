/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QFontDialog>
#include <QColorDialog>
#include "scorepropertiesdialog.h"
#include "ui_scorepropertiesdialog.h"

ScorePropertiesDialog::ScorePropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScorePropertiesDialog)
{
    ui->setupUi(this);

    createConnections();
}

void ScorePropertiesDialog::createConnections()
{
    connect(ui->titleLineEdit, SIGNAL(textChanged(QString)),
            this, SIGNAL(titleChanged(QString)));
    connect(ui->titleFontPushButton, SIGNAL(clicked()),
            this, SLOT(titleFontChangeClicked()));
    connect(ui->titleColorPushButton, SIGNAL(clicked()),
            this, SLOT(titleColorChangeClicked()));
}

ScorePropertiesDialog::~ScorePropertiesDialog()
{
    delete ui;
}

void ScorePropertiesDialog::setTitle(const QString &title)
{
    ui->titleLineEdit->setText(title);
}

void ScorePropertiesDialog::setComposer(const QString &composer)
{

}

void ScorePropertiesDialog::setArranger(const QString &arranger)
{

}

void ScorePropertiesDialog::setYear(const QString &year)
{

}

void ScorePropertiesDialog::setCopyright(const QString &copyright)
{

}

void ScorePropertiesDialog::setTimeSignature(const TimeSignature &timeSig)
{

}

void ScorePropertiesDialog::titleFontChangeClicked()
{
    bool ok = false;
    QFont newFont = QFontDialog::getFont(&ok, this);
    if (ok) {
        emit titleFontChanged(newFont);
    }
}

void ScorePropertiesDialog::titleColorChangeClicked()
{
    QColor newColor = QColorDialog::getColor(QColor(Qt::black), this);
    if (!newColor.isValid())
        return;

    emit titleColorChanged(newColor);
}
