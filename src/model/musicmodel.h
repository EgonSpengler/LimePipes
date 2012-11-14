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
#include <QHash>
#include <instrumentmanager.h>
#include <musicmodelinterface.h>
#include <musicitem.h>

class QXmlStreamWriter;
class QXmlStreamReader;
class QUndoStack;

class MusicModel :  public QAbstractItemModel,
        public MusicModelInterface
{
    Q_OBJECT

    friend class InsertItemsCommand;
    friend class RemoveItemsCommand;

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

    bool removeRows(int row, int count, const QModelIndex &parent);

    Qt::DropActions supportedDropActions() const { return Qt::MoveAction; }
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &parent);

    // MusicModelInterface
    QModelIndex insertScore(int row, const QString &title);
    QModelIndex appendScore(const QString &title);
    QModelIndex insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName);
    QModelIndex appendTuneToScore(const QModelIndex &score, const QString &instrumentName);
    QModelIndex insertTuneWithScore(int rowOfScore, const QString &scoreTitle, const QString &instrumentName);
    QModelIndex insertSymbol(int row, const QModelIndex &tune, const QString &symbolName);
    void insertPart(int partPosition, const QModelIndex &tuneIndex, int measures, bool withRepeat=false);

    MusicItem *itemForIndex(const QModelIndex& index) const;

    bool isIndexScore(const QModelIndex &index) const;
    bool isIndexTune(const QModelIndex &index) const;
    bool isIndexSymbol(const QModelIndex &index) const;
    bool indexSupportsWritingOfData(const QModelIndex &index, int role) const;

    void clear();

    QStringList instrumentNames() const { return m_instrumentManager->instrumentNames(); }
    QStringList symbolNamesForInstrument(const QString &instrument) const { return m_instrumentManager->symbolNamesForInstrument(instrument); }

    void save(const QString &filename);
    void load(const QString &filename);

    QUndoStack *undoStack() const { return m_undoStack; }

private:
    bool allModelIndexesHaveTheSameMusicItemType(const QModelIndexList &indexes) const;
    const QString mimeTypeForItem(const MusicItem *item) const;
    bool dataHasSupportedMimeType(const QMimeData *data);
    bool itemSupportsDropOfMimeType(const MusicItem *item, const QString &mimeType);

    void writeMusicItemAndChildren(QXmlStreamWriter *writer, MusicItem *musicItem) const;

    void writeTuneAttributes(QXmlStreamWriter *writer, MusicItem *musicItem) const;
    void writeSymbolAttributes(QXmlStreamWriter *writer, MusicItem *musicItem) const;

    void readMusicItems(QXmlStreamReader *reader, MusicItem *item);

    void processScoreTag(QXmlStreamReader *reader, MusicItem **item);
    void processTuneTag(QXmlStreamReader *reader, MusicItem **item);
    void processSymbolTag(QXmlStreamReader *reader, MusicItem **item);
    void readPitchIfSymbolHasPitch(QXmlStreamReader *reader, MusicItem **item);

    bool isEndTagOfCurrentItem(QXmlStreamReader *reader, MusicItem *item);
    bool isValidSymbolTag(QXmlStreamReader *reader, MusicItem *item);
    bool isValidTuneTag(QXmlStreamReader *reader);
    bool isValidScoreTag(QXmlStreamReader *reader);

    bool tagHasNonEmptyAttribute(QXmlStreamReader *reader, const QString &attributeName);
    bool tagHasNameOfItemType(QStringRef tagname, MusicItem::Type type);

    bool instrumentNameIsSupported(const QString &instrumentName);
    bool symbolNameIsSupported(QXmlStreamReader *reader, MusicItem *tuneItem);

    MusicItem *newTuneWithInstrument(QXmlStreamReader *reader, MusicItem *item);
    MusicItem *newSymbolForTuneItem(QXmlStreamReader *reader, MusicItem *item);

    InstrumentPtr instrumentFromItem(MusicItem *item);
    template<typename T>
    T *itemPointerToNewChildItem(MusicItem **parent);

    QString attributeValue(QXmlStreamReader *reader, const QString &attributeName);

    const QString tagNameOfMusicItemType(MusicItem::Type type) const;

    bool indexHasItemType(const QModelIndex &index, MusicItem::Type type) const;
    void createRootItemIfNotPresent();
    bool isRowValid(MusicItem *item, int row) const;

    static QHash<int, QString> initItemTypeTags();
    bool isMusicItemTag(const QString &tagName);
    bool isMusicItemTag(const QStringRef &tagName);

    QModelIndex insertItem(const QString &text, const QModelIndex &parent, int row, MusicItem *item);

    MusicItem *m_rootItem;
    int m_columnCount;
    InstrumentManager *m_instrumentManager;
    static QHash<int, QString> s_itemTypeTags;
    QUndoStack *m_undoStack;
    bool m_dropMimeDataOccured;
};

#endif // MUSICMODEL_H
