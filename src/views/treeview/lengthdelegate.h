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
#include <symbol.h>

class LengthDelegate : public MusicSymbolDataDelegate
{
    Q_OBJECT
public:
    explicit LengthDelegate(QObject *parent = 0);
    QStringList comboBoxItems(const Symbol *symbol) const;
    bool hasSymbolDelegateData(const Symbol *symbol) const
        { return symbol->hasLength(); }
    void setSymbolDataFromSelectedText(Symbol *symbol, const QString &text) const;
    QString currentSelectedData(const Symbol *symbol) const
        { return QString::number(symbol->length()); }
};

#endif // LENGTHDELEGATE_H
