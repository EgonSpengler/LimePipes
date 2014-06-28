/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "musicproxymodel.h"
#include <musicmodel.h>
#include <common/itemdataroles.h>
#include <common/datatypes/length.h>

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
            return index.data(LP::ScoreTitle);

        if (model->isIndexTune(srcIndex)) {
            int instrumentType = srcIndex.data(LP::TuneInstrument).toInt();
            InstrumentMetaData instrument = m_pluginManager->instrumentMetaData(instrumentType);
                return instrument.name() + " tune";
        }

        if (model->isIndexSymbol(srcIndex))
            return index.data(LP::SymbolName);
        if (model->isIndexPart(srcIndex))
            return QString("Part");
        if (model->isIndexMeasure(srcIndex))
            return QString("Measure");
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
            QVariant pitchVar = srcIndex.data(LP::SymbolPitch);
            if (pitchVar.canConvert<Pitch>()) {
                Pitch pitch = pitchVar.value<Pitch>();
                return pitch.name();
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
            QVariant lengthVar = srcIndex.data(LP::SymbolLength);
            if (lengthVar.canConvert<Length::Value>()) {
                Length::Value length = lengthVar.value<Length::Value>();
                return length;
            }
        }
    }
    return QSortFilterProxyModel::data(index, role);
}
PluginManager MusicProxyModel::pluginManager() const
{
    return m_pluginManager;
}

void MusicProxyModel::setPluginManager(const PluginManager &pluginManager)
{
    m_pluginManager = pluginManager;
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

QModelIndex MusicProxyModel::insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcIndex = mapToSource(score);
        return mapFromSource(model->insertTuneIntoScore(row, srcIndex, instrumentName));
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::insertTuneWithScore(int rowOfScore, const QString &scoreTitle, const QString &instrumentName)
{
    if (MusicModel *model = musicModel()) {
        return mapFromSource(model->insertTuneWithScore(rowOfScore, scoreTitle, instrumentName));
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::appendTuneToScore(const QModelIndex &score, const QString &instrumentName)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcScoreIndex = mapToSource(score);
        QModelIndex srcIndex = model->appendTuneToScore(srcScoreIndex, instrumentName);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::insertPartIntoTune(int row, const QModelIndex &tune, int measures, bool withRepeat)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcTuneIndex = mapToSource(tune);
        QModelIndex srcIndex = model->insertPartIntoTune(row, srcTuneIndex, measures, withRepeat);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::appendPartToTune(const QModelIndex &tune, int measures, bool withRepeat)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcTuneIndex = mapToSource(tune);
        QModelIndex srcIndex = model->appendPartToTune(srcTuneIndex, measures, withRepeat);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::insertMeasureIntoPart(int row, const QModelIndex &part)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcPartIndex = mapToSource(part);
        QModelIndex srcIndex = model->insertMeasureIntoPart(row, srcPartIndex);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::appendMeasureToPart(const QModelIndex &part)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcPartIndex = mapToSource(part);
        QModelIndex srcIndex = model->appendMeasureToPart(srcPartIndex);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::insertSymbolIntoMeasure(int row, const QModelIndex &measure, int type)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcMeasureIndex = mapToSource(measure);
        QModelIndex srcIndex = model->insertSymbolIntoMeasure(row, srcMeasureIndex, type);
        return mapFromSource(srcIndex);
    }
    return QModelIndex();
}

QModelIndex MusicProxyModel::appendSymbolToMeasure(const QModelIndex &measure, int type)
{
    if (MusicModel *model = musicModel()) {
        QModelIndex srcMeasureIndex = mapToSource(measure);
        QModelIndex srcIndex = model->appendSymbolToMeasure(srcMeasureIndex, type);
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

void MusicProxyModel::save(const QString &filename)
{
    if (MusicModel *model = musicModel()) {
        model->setFilename(this->filename());
        model->save(filename);
    }
}

void MusicProxyModel::load(const QString &filename)
{
    if (MusicModel *model = musicModel()) {
        model->setFilename(filename);
        model->load(filename);
    }
}

QUndoStack *MusicProxyModel::undoStack() const
{
    if (MusicModel *model = musicModel()) {
        return model->undoStack();
    }
    return 0;
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

bool MusicProxyModel::isIndexPart(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex partIndex = mapToSource(index);
        return model->isIndexPart(partIndex);
    }
    return false;
}

bool MusicProxyModel::isIndexMeasure(const QModelIndex &index) const
{
    if (MusicModel *model = musicModel()) {
        QModelIndex measureIndex = mapToSource(index);
        return model->isIndexMeasure(measureIndex);
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
