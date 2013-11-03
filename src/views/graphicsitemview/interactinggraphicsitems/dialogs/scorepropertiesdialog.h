/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESDIALOG_H
#define SCOREPROPERTIESDIALOG_H

#include <QDialog>

namespace Ui {
class ScorePropertiesDialog;
}

class TimeSignature;

class ScorePropertiesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ScorePropertiesDialog(QWidget *parent = 0);
    ~ScorePropertiesDialog();
    
private slots:
    // ScorePropertiesInterface interface
    void setTitle(const QString &title);
    void setComposer(const QString &composer);
    void setArranger(const QString &arranger);
    void setYear(const QString &year);
    void setCopyright(const QString &copyright);
    void setTimeSignature(const TimeSignature &timeSig);

    void titleFontChangeClicked();
    void titleColorChangeClicked();

signals:
    void titleChanged(const QString& newTitle);
    void titleFontChanged(const QFont& font);
    void titleColorChanged(const QColor& color);
    void composerChanged(const QString& newComposer);
    void arrangerChanged(const QString& newArranger);
    void yearChanged(const QString& newYear);
    void copyrightChanged(const QString& newCopyright);
    void timeSignatureChanged(const TimeSignature& newTimeSignature);

private:
    void createConnections();
    Ui::ScorePropertiesDialog *ui;
};

#endif // SCOREPROPERTIESDIALOG_H
