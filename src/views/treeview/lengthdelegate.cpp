/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "lengthdelegate.h"

LengthDelegate::LengthDelegate(QObject *parent) :
    MusicSymbolDataDelegate(parent)
{
}

QStringList LengthDelegate::comboBoxItems(const Symbol *symbol) const
{
    Q_UNUSED(symbol)
    QStringList items;
    foreach (int length, Length::lengthValues()) {
        items << QString::number(length);
    }
    return items;
}

void LengthDelegate::setSymbolDataFromSelectedText(Symbol *symbol, const QString &text) const
{
    bool conversionOk;
    int length = text.toInt(&conversionOk);
    if (!conversionOk)
        return;

    if (Length::lengthValues().contains(length)) {
        symbol->setData(QVariant::fromValue<Length::Value>((Length::Value)length), LP::symbolLength);
    }
}
