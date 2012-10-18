/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef LENGTHDELEGATE_H
#define LENGTHDELEGATE_H

#include "musicsymboldatadelegate.h"

class LengthDelegate : public MusicSymbolDataDelegate
{
    Q_OBJECT
public:
    explicit LengthDelegate(QObject *parent = 0)
        : MusicSymbolDataDelegate(parent) {}

    QStringList comboBoxItems(const QModelIndex &symbolIndex) const;
    QString currentSelectedData(const QModelIndex &symbolIndex) const;
    bool hasSymbolDelegateData(const QModelIndex &symbolIndex) const;
    void setSymbolDataFromSelectedText(QAbstractItemModel *model, const QModelIndex &symbolIndex, const QString &text) const;
};

#endif // LENGTHDELEGATE_H
