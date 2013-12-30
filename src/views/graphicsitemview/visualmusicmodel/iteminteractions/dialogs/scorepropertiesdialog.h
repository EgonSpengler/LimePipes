/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SCOREPROPERTIESDIALOG_H
#define SCOREPROPERTIESDIALOG_H

#include <QHash>
#include <QDialog>
#include <itemdatatypes.h>

namespace Ui {
class ScorePropertiesDialog;
}

class QFont;
class QColor;
class QSignalMapper;
class TextPropertyEditWidget;

class ScorePropertiesDialog : public QDialog
{
    Q_OBJECT

    friend class ScorePropertiesDialogTest;

public:
    explicit ScorePropertiesDialog(QWidget *parent = 0);
    ~ScorePropertiesDialog();

    void setPropertyText(int dataRole, const QString& text);
    QString propertyText(int dataRole) const;

    TextPropertyEditWidget *textEditWidgetForRole(int dataRole) const;

signals:
    void propertyTextChanged(LP::ScoreDataRole dataRole, const QString& text);

private:
    void addTextEditWidget(int layoutRow, LP::ScoreDataRole dataRole, const QString& text);
    QHash<int, TextPropertyEditWidget*> m_textEditWidgets;
    Ui::ScorePropertiesDialog *ui;
};

#endif // SCOREPROPERTIESDIALOG_H
