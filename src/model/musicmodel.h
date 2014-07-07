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
#include <musicmodelinterface.h>
#include <musicitem.h>
#include <common/pluginmanagerinterface.h>

class QXmlStreamWriter;
class QXmlStreamReader;
class QUndoStack;

class MusicModel : public QAbstractItemModel,
                   public MusicModelInterface
{
    Q_OBJECT

    friend class InsertItemsCommand;
    friend class RemoveItemsCommand;

public:
    explicit MusicModel(QObject *parent = 0);
    ~MusicModel();

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
    QModelIndex insertPartIntoTune(int row, const QModelIndex &tune, int measures, bool withRepeat=false);
    QModelIndex appendPartToTune(const QModelIndex &tune, int measures, bool withRepeat=false);
    QModelIndex insertMeasureIntoPart(int row, const QModelIndex &part);
    QModelIndex appendMeasureToPart(const QModelIndex &part);
    QModelIndex insertSymbolIntoMeasure(int row, const QModelIndex &measure, int type);
    QModelIndex appendSymbolToMeasure(const QModelIndex &measure, int type);

    MusicItem *itemForIndex(const QModelIndex& index) const;
    QModelIndex indexForItem(MusicItem *item) const;

    bool isIndexScore(const QModelIndex &index) const;
    bool isIndexTune(const QModelIndex &index) const;
    bool isIndexPart(const QModelIndex &index) const;
    bool isIndexMeasure(const QModelIndex &index) const;
    bool isIndexSymbol(const QModelIndex &index) const;
    bool indexSupportsWritingOfData(const QModelIndex &index, int role) const;

    void clear();

    void save(const QString &filename);
    void load(const QString &filename);

    QUndoStack *undoStack() const { return m_undoStack; }

    void setPluginManager(const PluginManager& pluginManager);

private:
    bool allModelIndexesHaveTheSameMusicItemType(const QModelIndexList &indexes) const;
    const QString mimeTypeForItem(const MusicItem *item) const;
    bool dataContainsOnlyOneSupportedMimeType(const QMimeData *data);
    QString supportedMimeTypeFromData(const QMimeData *data);
    bool itemSupportsDropOfMimeType(const MusicItem *item, const QString &mimeType);

    void writeMusicItemAndChildren(QXmlStreamWriter *writer, MusicItem *musicItem) const;

    void writeTuneAttributes(QXmlStreamWriter *writer, MusicItem *musicItem) const;
    void writeSymbolAttributes(QXmlStreamWriter *writer, MusicItem *musicItem) const;

    void readMusicItems(QXmlStreamReader *reader, MusicItem *item);

    void processScoreTag(QXmlStreamReader *reader, MusicItem **item);
    void processTuneTag(QXmlStreamReader *reader, MusicItem **item);
    void processPartTag(QXmlStreamReader *reader, MusicItem **item);
    void processMeasureTag(QXmlStreamReader *reader, MusicItem **item);
    void processSymbolTag(QXmlStreamReader *reader, MusicItem **item);
    void readPitchIfSymbolHasPitch(QXmlStreamReader *reader, MusicItem **item);

    bool isEndTagOfCurrentItem(QXmlStreamReader *reader, MusicItem *item);
    bool isValidSymbolTag(QXmlStreamReader *reader, MusicItem *item);
    bool isValidTuneTag(QXmlStreamReader *reader);
    bool isValidPartTag(QXmlStreamReader *reader);
    bool isValidMeasureTag(QXmlStreamReader *reader);
    bool isValidScoreTag(QXmlStreamReader *reader);

    bool tagHasNonEmptyAttribute(QXmlStreamReader *reader, const QString &attributeName);
    bool tagHasNameOfItemType(QStringRef tagname, LP::ItemType type);

    bool instrumentNameIsSupported(const QString &instrumentName);
    bool symbolTypeIsSupportedByTuneItem(QXmlStreamReader *reader, MusicItem *tuneItem);

    MusicItem *newTuneWithInstrument(QXmlStreamReader *reader, MusicItem *item);
    MusicItem *newSymbolForMeasureItem(QXmlStreamReader *reader, MusicItem *item);
    MusicItem *getTuneItemParent(MusicItem *item);

    InstrumentMetaData instrumentFromItem(MusicItem *item) const;
    template<typename T>
    T *itemPointerToNewChildItem(MusicItem **parent);

    QString attributeValue(QXmlStreamReader *reader, const QString &attributeName);

    const QString tagNameOfMusicItemType(LP::ItemType type) const;

    bool indexHasItemType(const QModelIndex &index, LP::ItemType type) const;
    void createRootItemIfNotPresent();
    bool isRowValid(MusicItem *item, int row) const;

    static QHash<LP::ItemType, QString> initItemTypeTags();
    bool isMusicItemTag(const QString &tagName);
    bool isMusicItemTag(const QStringRef &tagName);

    QModelIndex insertItem(const QString &text, const QModelIndex &parent, int row, MusicItem *item);
    QModelIndex insertItems(const QString &text, const QModelIndex &parent, int row, const QList<MusicItem *> &items);

    // Candidate for public api
    QModelIndex insertSpanningSymbolIntoMeasure(int row, const QModelIndex &measure, int type);

    MusicItem *m_rootItem;
    int m_columnCount;
    PluginManager m_pluginManager;
    static QHash<LP::ItemType, QString> s_itemTypeTags;
    QUndoStack *m_undoStack;
    bool m_dropMimeDataOccured;

    // Fixes Qt Bug #6679.
    // This Bug should be fixed in Qt in a newer version (4.8.x).
    // After that, this variable can be removed and the root CMakeLists.txt should contain
    // an entry for the required minimum Qt Version ( find_package( Qt4 4.8.x REQUIRED ))
    bool m_noDropOccured;
};

namespace LP {

uint qHash(const LP::ItemType &itemType);

}

#endif // MUSICMODEL_H
