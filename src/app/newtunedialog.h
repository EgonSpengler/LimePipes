/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef NEWTUNEDIALOG_H
#define NEWTUNEDIALOG_H

#include <QDialog>

namespace Ui {
class NewTuneDialog;
}

class NewTuneDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewTuneDialog(const QList<QString> &instruments, QWidget *parent = 0);
    ~NewTuneDialog();
    QString scoreTitle() const;
    QString instrumentTitle() const;
    
private:
    Ui::NewTuneDialog *ui;
};

#endif // NEWTUNEDIALOG_H
