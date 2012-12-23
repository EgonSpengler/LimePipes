/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pitchdelegate.h"
#include <musicmodelinterface.h>
#include <itemdatatypes.h>
#include <datatypes/pitch.h>
#include <datatypes/pitchcontext.h>
#include <datatypes/instrument.h>

QStringList PitchDelegate::comboBoxItems(const QModelIndex &symbolIndex) const
{
    QModelIndex tune = symbolIndex.parent();
    QVariant instrumentVar = tune.data(LP::tuneInstrument);

    if (instrumentVar.canConvert<InstrumentPtr>()) {
        InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
        return instrument->pitchNames();
    }
    return QStringList();
}

bool PitchDelegate::hasSymbolDelegateData(const QModelIndex &symbolIndex) const
{
    const MusicModelInterface *musicModel = dynamic_cast<const MusicModelInterface*>(symbolIndex.model());
    if (musicModel) {
        return musicModel->indexSupportsWritingOfData(symbolIndex, LP::symbolPitch);
    }
    return false;
}

QString PitchDelegate::currentSelectedData(const QModelIndex &symbolIndex) const
{
    QVariant pitchVar = symbolIndex.data(LP::symbolPitch);
    if (pitchVar.canConvert<PitchPtr>()) {
        PitchPtr pitch = pitchVar.value<PitchPtr>();
        return pitch->name();
    }
    return "";
}

void PitchDelegate::setSymbolDataFromSelectedText(QAbstractItemModel *model, const QModelIndex &symbolIndex, const QString &text) const
{
    QModelIndex tune = symbolIndex.parent();
    QVariant instrumentVar = tune.data(LP::tuneInstrument);

    if (instrumentVar.canConvert<InstrumentPtr>()) {
        InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
        PitchContextPtr pitchContext = instrument->pitchContext();
        PitchPtr pitch = pitchContext->pitchForName(text);
        model->setData(symbolIndex, QVariant::fromValue<PitchPtr>(pitch), LP::symbolPitch);
    }
}
