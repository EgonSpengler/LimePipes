/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "lengthdelegate.h"
#include <musicmodelinterface.h>
#include <itemdatatypes.h>
#include <datatypes/length.h>

QStringList LengthDelegate::comboBoxItems(const QModelIndex &symbolIndex) const
{
    Q_UNUSED(symbolIndex)
    QStringList items;
    foreach (int length, Length::lengthValues()) {
        items << QString::number(length);
    }
    return items;
}

bool LengthDelegate::hasSymbolDelegateData(const QModelIndex &symbolIndex) const
{
    const MusicModelInterface *musicModel = dynamic_cast<const MusicModelInterface*>(symbolIndex.model());
    if (musicModel) {
        return musicModel->indexSupportsWritingOfData(symbolIndex, LP::symbolLength);
    }
    return false;
}

void LengthDelegate::setSymbolDataFromSelectedText(QAbstractItemModel *model, const QModelIndex &symbolIndex, const QString &text) const
{
    bool conversionOk;
    int length = text.toInt(&conversionOk);
    if (!conversionOk)
        return;

    if (Length::lengthValues().contains(length)) {
        QVariant lengthVar = QVariant::fromValue<Length::Value>((Length::Value)length);
        model->setData(symbolIndex, lengthVar, LP::symbolLength);
    }
}

QString LengthDelegate::currentSelectedData(const QModelIndex &symbolIndex) const
{
    QVariant lengthVar = symbolIndex.data(LP::symbolLength);
    if (lengthVar.canConvert<Length::Value>()) {
        Length::Value length = lengthVar.value<Length::Value>();
        return QString::number(length);
    }
    return QString();
}
