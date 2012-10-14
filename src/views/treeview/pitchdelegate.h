/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PITCHDELEGATE_H
#define PITCHDELEGATE_H

#include "musicsymboldatadelegate.h"
#include <symbol.h>

class PitchDelegate : public MusicSymbolDataDelegate
{
    Q_OBJECT
public:
    explicit PitchDelegate(QObject *parent = 0)
        : MusicSymbolDataDelegate(parent) {}

    QStringList comboBoxItems(const Symbol *symbol) const;
    bool hasSymbolDelegateData(const Symbol *symbol) const
        { return symbol->hasPitch(); }
    QString currentSelectedData(const Symbol *symbol) const
        { return symbol->pitch()->name(); }
    void setSymbolDataFromSelectedText(Symbol *symbol, const QString &text) const;
};

#endif // PITCHDELEGATE_H
