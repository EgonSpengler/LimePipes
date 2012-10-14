/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicproxymodel.h"
#include <itemdatatypes.h>
#include <tune.h>
#include <score.h>

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
            Tune *tune = model->tuneFromIndex(srcIndex);
            if (tune) {
                return tune->instrument()->name() + " tune";
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
            Symbol *symbol = model->symbolFromIndex(srcIndex);
            if (symbol && symbol->hasPitch()) {
                return symbol->pitch()->name();
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
            Symbol *symbol = model->symbolFromIndex(srcIndex);
            if (symbol && symbol->hasLength()) {
                return symbol->length();
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
        return model->insertScore(row, title);
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
        return model->insertTuneIntoScore(row, srcIndex, instrument);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::insertTuneWithScore(int rowOfScore, const QString &scoreTitle, InstrumentPtr instrument)
{
    if (MusicModel *model = musicModel()) {
        return model->insertTuneWithScore(rowOfScore, scoreTitle, instrument);
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
        return itemForIndex(srcIndex);
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

Score *MusicProxyModel::scoreFromIndex(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return model->scoreFromIndex(srcIndex);
    }
    return new Score();
}

Tune *MusicProxyModel::tuneFromIndex(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return model->tuneFromIndex(srcIndex);
    }
    return new Tune();
}

Symbol *MusicProxyModel::symbolFromIndex(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return model->symbolFromIndex(srcIndex);
    }
    return new Symbol();
}

PitchContextPtr MusicProxyModel::pitchContextFromTuneIndex(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(index);
        return model->pitchContextFromTuneIndex(srcIndex);
    }
    return PitchContextPtr(new PitchContext());
}
