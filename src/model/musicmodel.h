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
#include <instrumentmanager.h>
#include <musicmodelinterface.h>
#include <musicitem.h>

class MusicModel :  public QAbstractItemModel,
                    public MusicModelInterface
{
    Q_OBJECT

public:
    explicit MusicModel(QObject *parent = 0);
    ~MusicModel();

    QDir pluginsDir();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    int columnCount(const QModelIndex &parent) const;
    void setColumnCount(int columns);

    // MusicModelInterface
    QModelIndex insertScore(int row, const QString &title);
    QModelIndex appendScore(const QString &title);
    QModelIndex insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName);
    QModelIndex appendTuneToScore(const QModelIndex &score, const QString &instrumentName);
    QModelIndex insertTuneWithScore(int rowOfScore, const QString &scoreTitle, const QString &instrumentName);
    QModelIndex insertSymbol(int row, const QModelIndex &tune, const QString &symbolName);
    
    MusicItem *itemForIndex(const QModelIndex& index) const;

    bool isIndexScore(const QModelIndex &index) const;
    bool isIndexTune(const QModelIndex &index) const;
    bool isIndexSymbol(const QModelIndex &index) const;
    bool indexSupportsWritingOfData(const QModelIndex &index, int role) const;

    void clear();

    QStringList instrumentNames() const { return m_instrumentManager->instrumentNames(); }
    QStringList symbolNamesForInstrument(const QString &instrument) const { return m_instrumentManager->symbolNamesForInstrument(instrument); }

private:
    bool indexHasItemType(const QModelIndex &index, MusicItem::Type type) const;
    void createRootItemIfNotPresent();
    bool isRowValid(MusicItem *item, int row) const;

    template<class T>
    T castedMusicItemFromIndex(const QModelIndex &index) const;

    QModelIndex insertItem(int row, const QModelIndex &parent, MusicItem *item);
    MusicItem *m_rootItem;
    int m_columnCount;
    InstrumentManager *m_instrumentManager;
};

#endif // MUSICMODEL_H
