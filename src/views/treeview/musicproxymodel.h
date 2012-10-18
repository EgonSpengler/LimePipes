/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICPROXYMODEL_H
#define MUSICPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <musicmodelinterface.h>

class MusicModel;

class MusicProxyModel : public QSortFilterProxyModel,
                        public MusicModelInterface
{
    Q_OBJECT
public:
    enum Columns {
        ItemColumn = 0,
        PitchColumn,
        LengthColumn
    };

    explicit MusicProxyModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setSourceModel(QAbstractItemModel *sourceModel);

    // MusicModelInterface
    QModelIndex insertScore(int row, const QString &title);
    QModelIndex appendScore(const QString &title);
    QModelIndex insertTuneIntoScore(int row, const QModelIndex &score, InstrumentPtr instrument);
    QModelIndex insertTuneWithScore(int rowOfScore, const QString &scoreTitle, InstrumentPtr instrument);
    QModelIndex appendTuneToScore(const QModelIndex &score, InstrumentPtr instrument);
    QModelIndex insertSymbol(int row, const QModelIndex &tune, Symbol *symbol);

    MusicItem *itemForIndex(const QModelIndex &index) const;
    void clear();
    bool isIndexScore(const QModelIndex &index) const;
    bool isIndexTune(const QModelIndex &index) const;
    bool isIndexSymbol(const QModelIndex &index) const;
    bool indexSupportsWritingOfData(const QModelIndex &index, int role) const;

private:
    MusicModel *musicModel() const;
    QVariant itemColumnData(const QModelIndex &index, int role) const;
    QVariant pitchColumnData(const QModelIndex &index, int role) const;
    QVariant lengthColumnData(const QModelIndex &index, int role) const;
};

#endif // MUSICPROXYMODEL_H
