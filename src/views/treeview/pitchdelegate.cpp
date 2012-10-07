/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pitchdelegate.h"
#include <itemdatatypes.h>
#include <tune.h>

QStringList PitchDelegate::comboBoxItems(const Symbol *symbol) const
{
    Tune *tune = static_cast<Tune*>(symbol->parent());
    if (tune) {
        return tune->instrument()->pitchNames();
    }
    return QStringList();
}

void PitchDelegate::setSymbolDataFromSelectedText(Symbol *symbol, const QString &text) const
{
    Tune *tune = static_cast<Tune*>(symbol->parent());
    if (tune) {
        PitchContextPtr pitchContext = tune->instrument()->pitchContext();
        PitchPtr pitch = pitchContext->pitchForName(text);
        symbol->setData(QVariant::fromValue<PitchPtr>(pitch), LP::symbolPitch);
    }
}
