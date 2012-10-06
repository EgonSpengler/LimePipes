/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "pitchdelegate.h"
#include <QComboBox>
#include <itemdatatypes.h>
#include <tune.h>

PitchDelegate::PitchDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *PitchDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    QComboBox *comboBox = new QComboBox(parent);
    return comboBox;
}

void PitchDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    const MusicModel *model = musicModelFromIndex(index);
    if (isSymbolIndexOk(index) == false)
        return;

    Symbol *symbol = model->symbolFromIndex(index);
    if (symbol->hasPitch() == false)
        return;

    Tune *tune = model->tuneFromIndex(index.parent());
    InstrumentPtr instrument = tune->instrument();
    comboBox->insertItems(0, instrument->pitchNames());

    int pitchIndex = comboBox->findText(symbol->pitch()->name());
    comboBox->setCurrentIndex(pitchIndex);
}

bool PitchDelegate::isSymbolIndexOk(const QModelIndex &index) const
{
    const MusicModel *model = musicModelFromIndex(index);
    if (model &&
        model->isIndexSymbol(index) &&
        model->isIndexTune(index.parent()))
        return true;
    return false;
}

const MusicModel *PitchDelegate::musicModelFromIndex(const QModelIndex &index) const
{
    return static_cast<const MusicModel*>(index.model());
}

void PitchDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Q_UNUSED(model)
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    const MusicModel *musicModel = musicModelFromIndex(index);
    if (!musicModel ||
        !isSymbolIndexOk(index))
        return;

    Symbol *symbol = musicModel->symbolFromIndex(index);
    PitchContextPtr pitchContext = musicModel->pitchContextFromTuneIndex(index.parent());
    PitchPtr pitch = pitchContext->pitchForName(comboBox->currentText());
    if (symbol)
        symbol->setData(QVariant::fromValue<PitchPtr>(pitch), LP::symbolPitch);
}

void PitchDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

