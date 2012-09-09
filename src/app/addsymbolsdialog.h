/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef ADDSYMBOLSDIALOG_H
#define ADDSYMBOLSDIALOG_H

#include <QDialog>

namespace Ui {
class AddSymbolsDialog;
}

class AddSymbolsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddSymbolsDialog(QWidget *parent = 0);
    ~AddSymbolsDialog();
    void setSymbolNames(const QStringList &symbolNames);

signals:
    void insertSymbol(const QString &symbolName);
    
private:
    Ui::AddSymbolsDialog *ui;

private slots:
    void insertSymbolClicked();
};

#endif // ADDSYMBOLSDIALOG_H
