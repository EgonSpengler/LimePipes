/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pitchdelegate.h"
#include <musicmodelinterface.h>
#include <common/itemdataroles.h>
#include <common/datatypes/pitch.h>
#include <common/datatypes/pitchcontext.h>
#include <common/datatypes/instrument.h>

QStringList PitchDelegate::comboBoxItems(const QModelIndex &symbolIndex) const
{
    QModelIndex tune = symbolIndex.parent().parent().parent();
    if (!tune.isValid()) return QStringList();

    int instrumentType = tune.data(LP::TuneInstrument).toInt();

    if (instrumentType != LP::NoInstrument) {
        InstrumentMetaData metaData = pluginManager()->instrumentMetaData(instrumentType);
        return metaData.pitchContext()->pitchNames();
    }
    return QStringList();
}

bool PitchDelegate::hasSymbolDelegateData(const QModelIndex &symbolIndex) const
{
    const MusicModelInterface *musicModel = dynamic_cast<const MusicModelInterface*>(symbolIndex.model());
    if (musicModel) {
        return musicModel->indexSupportsWritingOfData(symbolIndex, LP::SymbolPitch);
    }
    return false;
}

QString PitchDelegate::currentSelectedData(const QModelIndex &symbolIndex) const
{
    QVariant pitchVar = symbolIndex.data(LP::SymbolPitch);
    if (pitchVar.canConvert<Pitch>()) {
        Pitch pitch = pitchVar.value<Pitch>();
        return pitch.name();
    }
    return "";
}

void PitchDelegate::setSymbolDataFromSelectedText(QAbstractItemModel *model, const QModelIndex &symbolIndex, const QString &text) const
{
    QModelIndex tune = symbolIndex.parent().parent().parent();
    if (!tune.isValid()) return;

    int instrumentType = tune.data(LP::TuneInstrument).toInt();

    if (instrumentType != LP::NoInstrument) {
        InstrumentMetaData metaData = pluginManager()->instrumentMetaData(instrumentType);
        Pitch pitch = metaData.pitchContext()->pitchForName(text);
        model->setData(symbolIndex, QVariant::fromValue<Pitch>(pitch), LP::SymbolPitch);
    }
}
