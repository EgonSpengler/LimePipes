/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicproxymodel.h"
#include <musicmodel.h>
#include <itemdatatypes.h>
#include <length.h>

MusicProxyModel::MusicProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
}

QVariant MusicProxyModel::data(const QModelIndex &index, int role) const
{
    switch (index.column()) {
    case ItemColumn:
        return itemColumnData(index, role);
    case PitchColumn:
        return pitchColumnData(index, role);
    case LengthColumn:
        return lengthColumnData(index, role);
    }
    return QSortFilterProxyModel::data(index, role);
}

bool MusicProxyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        if (srcIndex.column() != ItemColumn) {
            srcIndex = model->index(srcIndex.row(), ItemColumn, srcIndex.parent());
        }
        return model->setData(srcIndex, value, role);
    }
    return QSortFilterProxyModel::setData(index, value, role);
}

QVariant MusicProxyModel::itemColumnData(const QModelIndex &index, int role) const
{
    MusicModel *model = musicModel();
    if (!model)
        return QVariant();
    QModelIndex srcIndex = mapToSource(index);

    if (role == Qt::DisplayRole) {

        if (model->isIndexScore(srcIndex))
            return index.data(LP::scoreTitle);

        if (model->isIndexTune(srcIndex)) {
            QVariant instrumentVar = srcIndex.data(LP::tuneInstrument);
            if (instrumentVar.canConvert<InstrumentPtr>()) {
                InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
                return instrument->name() + " tune";
            }
        }

        if (model->isIndexSymbol(srcIndex))
            return index.data(LP::symbolName);
    }
    return QSortFilterProxyModel::data(index, role);
}

QVariant MusicProxyModel::pitchColumnData(const QModelIndex &index, int role) const
{
    MusicModel *model = musicModel();
    if (!model)
        return QVariant();

    QModelIndex srcIndex = mapToSource(index);

    if (role == Qt::DisplayRole) {
        if (model->isIndexSymbol(srcIndex)) {
            QVariant pitchVar = srcIndex.data(LP::symbolPitch);
            if (pitchVar.canConvert<PitchPtr>()) {
                PitchPtr pitch = pitchVar.value<PitchPtr>();
                return pitch->name();
            }
        }
    }
    return QSortFilterProxyModel::data(index, role);
}

QVariant MusicProxyModel::lengthColumnData(const QModelIndex &index, int role) const
{
    MusicModel *model = musicModel();
    if (!model)
        return QVariant();

    QModelIndex srcIndex = mapToSource(index);

    if (role == Qt::DisplayRole) {
        if (model->isIndexSymbol(srcIndex)) {
            QVariant lengthVar = srcIndex.data(LP::symbolLength);
            if (lengthVar.canConvert<Length::Value>()) {
                Length::Value length = lengthVar.value<Length::Value>();
                return length;
            }
        }
    }
    return QSortFilterProxyModel::data(index, role);
}

QVariant MusicProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal &&
        role == Qt::DisplayRole) {
        if (section == ItemColumn)
            return tr("Music item");
        if (section == PitchColumn)
            return tr("Pitch");
        if (section == LengthColumn)
            return tr("Length");
    }
    return QVariant();
}

void MusicProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);

    MusicModel *model = musicModel();
    if (model)
        model->setColumnCount(3);
}

MusicModel *MusicProxyModel::musicModel() const
{
    return static_cast<MusicModel*>(sourceModel());
}

QModelIndex MusicProxyModel::insertScore(int row, const QString &title)
{
    if (MusicModel *model = musicModel()) {
        return mapFromSource(model->insertScore(row, title));
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::appendScore(const QString &title)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = model->appendScore(title);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::insertTuneIntoScore(int row, const QModelIndex &score, InstrumentPtr instrument)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(score);
        return mapFromSource(model->insertTuneIntoScore(row, srcIndex, instrument));
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::insertTuneWithScore(int rowOfScore, const QString &scoreTitle, InstrumentPtr instrument)
{
    if (MusicModel *model = musicModel()) {
        return mapFromSource(model->insertTuneWithScore(rowOfScore, scoreTitle, instrument));
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::appendTuneToScore(const QModelIndex &score, InstrumentPtr instrument)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcScoreIndex = mapToSource(score);
        QModelIndex srcIndex = model->appendTuneToScore(srcScoreIndex, instrument);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::insertSymbol(int row, const QModelIndex &tune, Symbol *symbol)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcTuneIndex = mapToSource(tune);
        QModelIndex srcIndex = model->insertSymbol(row, srcTuneIndex, symbol);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

MusicItem *MusicProxyModel::itemForIndex(const QModelIndex &index) const
{
    if (musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return musicModel()->itemForIndex(srcIndex);
    }
    return 0;
}

void MusicProxyModel::clear()
{
    if (MusicModel *model = musicModel()) {
        model->clear();
    }
}

bool MusicProxyModel::isIndexScore(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return model->isIndexScore(srcIndex);
    }
    return false;
}

bool MusicProxyModel::isIndexTune(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return model->isIndexTune(srcIndex);
    }
    return false;
}

bool MusicProxyModel::isIndexSymbol(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return model->isIndexSymbol(srcIndex);
    }
    return false;
}

bool MusicProxyModel::indexSupportsWritingOfData(const QModelIndex &index, int role) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return model->indexSupportsWritingOfData(srcIndex, role);
    }
    return false;
}
