/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICMODEL_H
#define MUSICMODEL_H

#include <QAbstractItemModel>
#include <musicmodelinterface.h>
#include <musicitem.h>

class MusicModel :  public QAbstractItemModel,
                    public MusicModelInterface
{
    Q_OBJECT
public:
    explicit MusicModel(QObject *parent = 0) :
        QAbstractItemModel(parent), m_rootItem(0), m_columnCount(1) {}
    ~MusicModel() { delete m_rootItem; }

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    void setColumnCount(int columns);

    // MusicModelInterface
    QModelIndex insertScore(int row, const QString &title);
    QModelIndex appendScore(const QString &title);
    QModelIndex insertTuneIntoScore(int row, const QModelIndex &score, InstrumentPtr instrument);
    QModelIndex appendTuneToScore(const QModelIndex &score, InstrumentPtr instrument);
    QModelIndex insertTuneWithScore(int rowOfScore, const QString &scoreTitle, InstrumentPtr instrument);
    QModelIndex insertSymbol(int row, const QModelIndex &tune, Symbol *symbol);
    
    MusicItem *itemForIndex(const QModelIndex& index) const;
    void clear();
    bool isIndexScore(const QModelIndex &index) const;
    bool isIndexTune(const QModelIndex &index) const;
    bool isIndexSymbol(const QModelIndex &index) const;
    Score *scoreFromIndex(const QModelIndex &index) const;
    Tune *tuneFromIndex(const QModelIndex &index) const;
    Symbol *symbolFromIndex(const QModelIndex &index) const;
    PitchContextPtr pitchContextFromTuneIndex(const QModelIndex &index) const;

private:
    bool indexHasItemType(const QModelIndex &index, MusicItem::Type type) const;
    template<class T>
    T castedMusicItemFromIndex(const QModelIndex &index) const;
    void createRootItemIfNotPresent();
    bool isRowValid(MusicItem *item, int row) const;
    QModelIndex insertItem(int row, const QModelIndex &parent, MusicItem *item);
    MusicItem *m_rootItem;
    int m_columnCount;
};

#endif // MUSICMODEL_H
