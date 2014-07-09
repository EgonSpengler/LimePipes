/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

/*!
 * @class MusicModel
 * @brief The implementation of the QAbstractItemModel.
 *
 * @fn bool dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &parent);
 * @brief To keep the readMusicItems method simple, this method uses a temporary item for reading
 * the mime data. This is used because readMusicItems doesn't have a possibility to insert new items into a specific row
 * and always appends the read items.
 */

#include <QFile>
#include <QDebug>
#include <QMimeData>
#include <QPair>
#include <QString>
#include <QUndoStack>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include <commands/insertitemscommand.h>
#include <commands/removeitemscommand.h>
#include <common/defines.h>
#include <common/datatypes/timesignature.h>
#include <common/datahandling/mimedata.h>
#include <common/datahandling/datakeys.h>
#include <common/datahandling/symbolbehavior.h>
#include <utilities/error.h>

#include "rootitem.h"
#include "score.h"
#include "tune.h"
#include "part.h"
#include "measure.h"
#include "musicmodel.h"

namespace {

const int MaxTuneUnderScore = 3;  //!< From limepipes.xsd
const int MaxCompression = 9;

}

namespace LP {
uint qHash(const LP::ItemType &itemType)
{
    return static_cast<uint>(itemType);
}
}

using namespace LP;

QHash<LP::ItemType, QString> MusicModel::initItemTypeTags()
{
    QHash<LP::ItemType, QString> typeTags;
    typeTags.insert(ItemType::RootItemType, QString("LIMEPIPES"));
    typeTags.insert(ItemType::ScoreType,    QString("SCORE"));
    typeTags.insert(ItemType::TuneType,     QString("TUNE"));
    typeTags.insert(ItemType::PartType,     QString("PART"));
    typeTags.insert(ItemType::MeasureType,  QString("MEASURE"));
    typeTags.insert(ItemType::SymbolType,   QString("SYMBOL"));
    return typeTags;
}

MusicModel::MusicModel(QObject *parent)
    : QAbstractItemModel(parent), m_rootItem(0), m_columnCount(1),
      m_dropMimeDataOccured(false),
      m_noDropOccured(false)
{
    m_undoStack = new QUndoStack(this);
}

MusicModel::~MusicModel()
{
    delete m_rootItem;
}

Qt::ItemFlags MusicModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        theFlags |= Qt::ItemIsSelectable
                | Qt::ItemIsEnabled
                | Qt::ItemIsEditable;
        if (index.column() == 0) {
            theFlags |= Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
        }
    }
    return theFlags;
}

QModelIndex MusicModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!m_rootItem || row < 0 || column < 0 || column >= m_columnCount ||
            (parent.isValid() && parent.column() != 0))
        return QModelIndex();
    MusicItem *parentItem = itemForIndex(parent);
    Q_ASSERT(parentItem);
    if (MusicItem *item = parentItem->childAt(row))
        return createIndex(row, column, item);
    return QModelIndex();
}

QModelIndex MusicModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();
    if (MusicItem *childItem = itemForIndex(index)) {
        if (MusicItem *parentItem = childItem->parent()) {
            if (parentItem == m_rootItem)
                return QModelIndex();
            if (MusicItem *grandParentItem = parentItem->parent()) {
                int row = grandParentItem->rowOfChild(parentItem);
                return createIndex(row, 0, parentItem);
            }
        }
    }
    return QModelIndex();
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return 0;
    MusicItem *parentItem = itemForIndex(parent);
    return parentItem ? parentItem->childCount() : 0;
}

int MusicModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() && parent.column() != 0 ? 0 : m_columnCount;
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
    if (!m_rootItem || !index.isValid() || index.column() < 0 ||
            index.column() >= m_columnCount)
        return QVariant();

    if (MusicItem *item = itemForIndex(index)) {
        return item->data(role);
    }
    return QVariant();
}

bool MusicModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.column() != 0)
        return false;
    if (MusicItem *item = itemForIndex(index)) {
        if (item->data(role) == value)
            return false;

        if (item->setData(value, role)) {
            QVector<int> roles { role };
            emit dataChanged(index,index, roles);

            return true;
        }
    }
    return false;
}

void MusicModel::setColumnCount(int columns)
{
    if (columns < 1)
        return;
    m_columnCount = columns;
}

bool MusicModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > rowCount(parent) - 1)
        return false;
    if (row + count > rowCount(parent))
        return false;

    if (m_noDropOccured) {
        m_noDropOccured = false;
        return false;
    }

    if (!m_rootItem)
        return false;

    m_undoStack->push(new RemoveItemsCommand(this, "Remove items", parent, row, count));

    if (m_dropMimeDataOccured) {
        m_undoStack->endMacro();
        m_dropMimeDataOccured = false;
    }
    return true;
}

QStringList MusicModel::mimeTypes() const
{
    return QStringList() << LP::MimeTypes::Score << LP::MimeTypes::Tune << LP::MimeTypes::Symbol;
}

QMimeData *MusicModel::mimeData(const QModelIndexList &indexes) const
{
    Q_ASSERT(indexes.count());
    if (!allModelIndexesHaveTheSameMusicItemType(indexes))
        return 0;

    QJsonArray jsonArray;
    foreach (QModelIndex index, indexes) {
        if (MusicItem *item = itemForIndex(index)) {
            jsonArray.append(item->toJson());
        }
    }

    return MimeData::fromJsonArray(jsonArray);
}

bool MusicModel::allModelIndexesHaveTheSameMusicItemType(const QModelIndexList &indexes) const
{
    ItemType itemType = ItemType::NoItemType;
    MusicItem *item = 0;
    foreach (QModelIndex index, indexes) {
        item = itemForIndex(index);
        if (!item)
            return false;

        if (itemType == ItemType::NoItemType)
            itemType = item->type();
        else {
            if (item->type() != itemType) {
                qWarning() << "Not all indexes have the same type.";
                return false;
            }
        }
    }
    return true;
}

const QString MusicModel::mimeTypeForItem(const MusicItem *item) const
{
    switch (item->type()) {
    case ItemType::ScoreType:
        return LP::MimeTypes::Score;
    case ItemType::TuneType:
        return LP::MimeTypes::Tune;
    case ItemType::PartType:
        return LP::MimeTypes::Part;
    case ItemType::MeasureType:
        return LP::MimeTypes::Measure;
    case ItemType::SymbolType:
        return LP::MimeTypes::Symbol;
    default:
        qWarning() << "Mime type for MusicItem not supported.";
        return QString();
    }
}

bool MusicModel::dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row,
                              int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (action != Qt::MoveAction || column > 0 ||
            !mimeData || !dataContainsOnlyOneSupportedMimeType(mimeData))
        return false;

    if (isIndexTune(parent) &&
        row == -1) {
            row = rowCount(parent) - 1;
    }

    QString mimeType = supportedMimeTypeFromData(mimeData);

    createRootItemIfNotPresent();
    if (MusicItem *parentItem = itemForIndex(parent)) {
        if (!itemSupportsDropOfMimeType(parentItem, mimeType)) {
            m_noDropOccured = true;
            return false;
        }

        NullMusicItem tempParentItem(*parentItem);

        QJsonArray jsonArray = MimeData::toJsonArray(mimeData);
        foreach (const QJsonValue &value, jsonArray) {
            QJsonObject json = value.toObject();
            if (json.isEmpty())
                continue;

            MusicItem *item = itemFromJsonObject(json);
            tempParentItem.addChild(item);
        }

        if (!tempParentItem.childCount())
            return false;

        if (row == -1)  // Append to parent's childs
            row = parentItem->childCount();

        m_undoStack->beginMacro("Drop items");
        m_undoStack->push(new InsertItemsCommand(this, "Drop items", parent, row, tempParentItem.children()));
        m_dropMimeDataOccured = true;

        // Prevent temporary parent item from deleting childs in its destructor
        while (tempParentItem.childCount()) {
            MusicItem *item = tempParentItem.takeChild(0);
            item->setParent(parentItem);
        }

        Q_ASSERT(tempParentItem.childCount() == 0);
        return true;
    }
    return false;
}

MusicItem *MusicModel::itemFromJsonObject(const QJsonObject &json)
{
    LP::ItemType itemType = static_cast<LP::ItemType>(json.value(DataKey::ItemType).toInt());

    MusicItem *item = 0;
    switch (itemType) {
    case LP::ItemType::SymbolType: {
        int symbolType = json.value(DataKey::SymbolType).toInt();
        SymbolBehavior *behavior = m_pluginManager->symbolBehaviorForType(symbolType);
        if (!behavior)
            break;

        Symbol *symbol = new Symbol;
        symbol->setSymbolBehavior(behavior);
        symbol->fromJson(json);
        item = symbol;
        break;
    }
    case LP::ItemType::MeasureType: {
        Measure *measure = new Measure;
        measure->fromJson(json);
        item = measure;
        break;
    }
    case LP::ItemType::PartType: {
        Part *part = new Part;
        part->fromJson(json);
        item = part;
        break;
    }
    case LP::ItemType::TuneType: {
        Tune *tune = new Tune;
        tune->fromJson(json);
        item = tune;
        break;
    }
    case LP::ItemType::ScoreType: {
        Score *score = new Score;
        score->fromJson(json);
        item = score;
        break;
    }
    default: {
        qWarning() << "MusicModel: Can't get item from json object with type: "
                   << static_cast<int>(itemType);
        break;
    }
    }

    if (!item)
        return 0;

    QJsonArray childArray = json.value(DataKey::ItemChildren).toArray();
    if (!childArray.count()) {
        return item;
    }

    foreach (const QJsonValue &value, childArray) {
        QJsonObject childObject = value.toObject();
        if (childObject.isEmpty())
            continue;

        MusicItem *childItem = itemFromJsonObject(childObject);
        if (childItem)
            continue;

        item->addChild(childItem);
    }

    return item;
}

/*!
 * \brief MusicModel::dataContainsOnlyOneSupportedMimeType
 *        Check if the given mime data contains only one supported mime type of LimePipes.
 * \param data
 * \return True, if the mime data contains only one supported mime type, otherwise false.
 */
bool MusicModel::dataContainsOnlyOneSupportedMimeType(const QMimeData *data)
{
    QStringList dataFormats(data->formats());
    bool hasLimePipesFormat = false;
    if (dataFormats.contains(LP::MimeTypes::Symbol)) {
        hasLimePipesFormat = true;
    }
    if (dataFormats.contains(LP::MimeTypes::Measure)) {
        if (hasLimePipesFormat) { return false; }
        hasLimePipesFormat = true;
    }
    if (dataFormats.contains(LP::MimeTypes::Part)) {
        if (hasLimePipesFormat) { return false; }
        hasLimePipesFormat = true;
    }
    if (dataFormats.contains(LP::MimeTypes::Tune)) {
        if (hasLimePipesFormat) { return false; }
        hasLimePipesFormat = true;
    }
    if (dataFormats.contains(LP::MimeTypes::Score)) {
        if (hasLimePipesFormat) { return false; }
        hasLimePipesFormat = true;
    }

    return hasLimePipesFormat;
}

/*!
 * \brief MusicModel::supportedMimeTypeFromData Returns the first mime type from QMimeData,
 *        which is supported by LimePipes
 * \param data The mime data to check for supported mime type
 * \return The supported mime type or an empty string, if no supported mime type can be found.
 */
QString MusicModel::supportedMimeTypeFromData(const QMimeData *data)
{
    QStringList supportedMimeTypes({LP::MimeTypes::Symbol, LP::MimeTypes::Measure,
                                   LP::MimeTypes::Part, LP::MimeTypes::Tune,
                                   LP::MimeTypes::Score});
    foreach (const QString mimeType, data->formats()) {
        if (supportedMimeTypes.contains(mimeType)) {
            return mimeType;
        }
    }

    return QStringLiteral("");
}

bool MusicModel::itemSupportsDropOfMimeType(const MusicItem *item, const QString &mimeType)
{
    switch(item->type()) {
    case ItemType::RootItemType:
        if (mimeType == LP::MimeTypes::Score)
            return true;
        return false;
    case ItemType::ScoreType:
        if (mimeType == LP::MimeTypes::Tune)
            return true;
        return false;
    case ItemType::TuneType:
        if (mimeType == LP::MimeTypes::Part)
            return true;
        return false;
    case ItemType::PartType:
        if (mimeType == LP::MimeTypes::Measure)
            return true;
        return false;
    case ItemType::MeasureType:
        if (mimeType == LP::MimeTypes::Symbol)
            return true;
        return false;
    default:
        return false;
    }
}

QModelIndex MusicModel::insertScore(int row, const QString &title)
{
    createRootItemIfNotPresent();
    Q_ASSERT(m_rootItem->childType() == ItemType::ScoreType);

    QModelIndex scoreIndex = insertItem("Insert score", QModelIndex(), row, new Score(title));

    return scoreIndex;
}

QModelIndex MusicModel::appendScore(const QString &title)
{
    createRootItemIfNotPresent();
    return insertScore(m_rootItem->childCount(), title);
}

QModelIndex MusicModel::insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName)
{
    if (m_pluginManager.isNull()) {
        qWarning("No plugin manager installed. Can't insert tune into score.");
        return QModelIndex();
    }

    QList<int> instrumentTypes = m_pluginManager->instrumentTypes();
    int tuneInstrument = LP::NoInstrument;
    foreach (const int instrumentType, instrumentTypes) {
        if (m_pluginManager->instrumentMetaData(instrumentType).name() ==
                instrumentName) {
            tuneInstrument = instrumentType;
        }
    }

    if (tuneInstrument == LP::NoInstrument)
        return QModelIndex();

    return insertItem("Insert tune into score", score, row, new Tune(tuneInstrument));
}

QModelIndex MusicModel::appendTuneToScore(const QModelIndex &score, const QString &instrumentName)
{
    if (MusicItem *item = itemForIndex(score)) {
        return insertTuneIntoScore(item->childCount(), score, instrumentName);
    }
    return QModelIndex();
}

QModelIndex MusicModel::insertTuneWithScore(int rowOfScore, const QString &scoreTitle, const QString &instrumentName)
{
    m_undoStack->beginMacro(tr("Insert tune with score"));
    QModelIndex score = insertScore(rowOfScore, scoreTitle);
    QModelIndex tune = insertTuneIntoScore(0, score, instrumentName);
    m_undoStack->endMacro();
    return tune;
}

QModelIndex MusicModel::insertPartIntoTune(int row, const QModelIndex &tune, int measures, bool withRepeat)
{
    m_undoStack->beginMacro(tr("Insert part into tune"));
    int instrumentType = data(tune, LP::TuneInstrument).toInt();
    if (instrumentType == LP::NoInstrument)
        return QModelIndex();

    Part *newPart = new Part();
    InstrumentMetaData metaData = m_pluginManager->instrumentMetaData(instrumentType);
    newPart->setStaffType(metaData.staffType());
    newPart->setClefType(metaData.defaultClef());
    QModelIndex part = insertItem(tr("Insert part into tune"), tune, row, newPart);
    setData(part, QVariant::fromValue<bool>(withRepeat), LP::PartRepeat);
    for (int i=0; i<measures; i++) {
        Measure *measure = new Measure(m_pluginManager);
        measure->setData(tune.data(LP::TuneTimeSignature), LP::MeasureTimeSignature);
        insertItem(tr("Insert measure"), part, 0, measure);
    }
    m_undoStack->endMacro();
    return part;
}

QModelIndex MusicModel::appendPartToTune(const QModelIndex &tune, int measures, bool withRepeat)
{
    return insertPartIntoTune(rowCount(tune), tune, measures, withRepeat);
}

QModelIndex MusicModel::insertMeasureIntoPart(int row, const QModelIndex &part)
{
    if (m_pluginManager.isNull()) {
        qWarning("No plugin manager installed. Can't insert measure into part.");
        return QModelIndex();
    }

    MusicItem *partItem = itemForIndex(part);
    if (!partItem && partItem->type() == ItemType::PartType)
        return QModelIndex();

    QModelIndex tuneIndex = part.parent();
    Q_ASSERT(isIndexTune(tuneIndex));
    MusicItem *tuneItem = itemForIndex(tuneIndex);

    QVariant timeSigData = tuneItem->data(LP::TuneTimeSignature);
    if (!timeSigData.isValid() &&
            !timeSigData.canConvert<TimeSignature>())
        return QModelIndex();

    TimeSignature timeSig = timeSigData.value<TimeSignature>();
    Measure *measure = new Measure(m_pluginManager);
    measure->setData(QVariant::fromValue<TimeSignature>(timeSig), LP::MeasureTimeSignature);
    return insertItem(tr("Insert measure"), part, row, measure);
}

QModelIndex MusicModel::appendMeasureToPart(const QModelIndex &part)
{
    return insertMeasureIntoPart(rowCount(part), part);
}

QModelIndex MusicModel::insertSymbolIntoMeasure(int row, const QModelIndex &measure, int type)
{
    if (m_pluginManager.isNull()) {
        qWarning("No plugin manager installed. Can't insert symbol into measure.");
        return QModelIndex();
    }

    MusicItem *measureItem = itemForIndex(measure);
    if (!measureItem && measureItem->type() != ItemType::MeasureType)
        return QModelIndex();

    QModelIndex tuneIndex = measure.parent().parent();
    Q_ASSERT(isIndexTune(tuneIndex));
    MusicItem *tuneItem = itemForIndex(tuneIndex);

    int instrumentType = tuneItem->data(LP::TuneInstrument).toInt();
    if (instrumentType == LP::NoInstrument)
        return QModelIndex();

    InstrumentMetaData instrumentMeta = m_pluginManager->instrumentMetaData(instrumentType);
    SymbolCategory category = m_pluginManager->symbolMetaData(type).category();
    if (category == SymbolCategory::Spanning) {
        return insertSpanningSymbolIntoMeasure(row, measure, type);
    }

    Symbol *symbol = new Symbol();
    SymbolBehavior *symbolBehavior = m_pluginManager->symbolBehaviorForType(type);
    symbol->setSymbolBehavior(symbolBehavior);

    if (symbol == 0) {
        qWarning() << "MusicModel: Can't insert symbol. PluginManager returned 0 for symbol type "
                      << type;
        return QModelIndex();
    }

    symbol->setData(instrumentType, LP::SymbolInstrument);
    // Init pitch and pitch context if symbol has it
    if (symbol->hasPitch()) {
        PitchContextPtr pitchContext = instrumentMeta.pitchContext();
        int initialStaffPos = 0;
        if (pitchContext->lowestStaffPos() > initialStaffPos) {
            initialStaffPos = pitchContext->lowestStaffPos();
        }
        Pitch pitch = pitchContext->pitchForStaffPos(initialStaffPos);
        QVariant pitchValue(QVariant::fromValue<Pitch>(pitch));
        symbol->setData(pitchValue, LP::SymbolPitch);
    }

    if (symbol &&
            symbol->symbolType() == LP::NoSymbolType)
        return QModelIndex();
    QString insertText = tr("Insert %1").arg(symbol->data(LP::SymbolName).toString());

    return insertItem(insertText, measure, row, symbol);
}

QModelIndex MusicModel::insertSpanningSymbolIntoMeasure(int row, const QModelIndex &measure, int type)
{
    if (m_pluginManager.isNull()) {
        qWarning("No plugin manager installed. Can't insert spanning symbol into measure.");
        return QModelIndex();
    }

    Symbol *startSymbol = new Symbol();
    SymbolBehavior *startBehavior = m_pluginManager->symbolBehaviorForType(type);
    startSymbol->setSymbolBehavior(startBehavior);

    Symbol *endSymbol = new Symbol();
    SymbolBehavior *endBehavior = m_pluginManager->symbolBehaviorForType(type);
    endSymbol->setSymbolBehavior(endBehavior);
    if (startSymbol == 0 ||
            endSymbol == 0) {
        qWarning() << "MusicModel: Can't insert symbol. PluginManager returned 0 for symbol type "
                      << type;
        return QModelIndex();
    }

    startSymbol->setData(QVariant::fromValue<SpanType>(SpanType::Start),
                         LP::SymbolSpanType);
    endSymbol->setData(QVariant::fromValue<SpanType>(SpanType::End),
                         LP::SymbolSpanType);

    m_undoStack->beginMacro(tr("Insert %1 Items")
                            .arg(startSymbol->data(LP::SymbolName).toString()));
    QPersistentModelIndex endSymbolIndex = insertItem(QStringLiteral(""), measure, row, endSymbol);
    QPersistentModelIndex startSymbolIndex = insertItem(QStringLiteral(""), measure, row, startSymbol);
    m_undoStack->endMacro();

    return startSymbolIndex;
}


QModelIndex MusicModel::appendSymbolToMeasure(const QModelIndex &measure, int type)
{
    return insertSymbolIntoMeasure(rowCount(measure), measure, type);
}

MusicItem *MusicModel::itemForIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        if (MusicItem *item = static_cast<MusicItem*>(
                    index.internalPointer()))
            return item;
    }
    return m_rootItem;
}

QModelIndex MusicModel::indexForItem(MusicItem *item) const
{
    MusicItem *itemPtr = item;
    QVector<int> childRows;
    while (itemPtr->parent() != 0) {
        childRows.prepend(itemPtr->parent()->rowOfChild(itemPtr));
        itemPtr = itemPtr->parent();
    }

    QModelIndex indexOfItem = QModelIndex();
    for (int i=0; i<childRows.count(); i++) {
        indexOfItem = index(childRows[i], 0, indexOfItem);
    }
    return indexOfItem;
}

void MusicModel::clear()
{
    beginResetModel();
    delete m_rootItem;
    m_rootItem = 0;
    endResetModel();
}

void MusicModel::save(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;

    if (m_filename.isEmpty())
        throw LP::Error(tr("no filename specified"));

    QFile file(m_filename);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text))
        throw LP::Error(file.errorString());
}

void MusicModel::load(const QString &filename)
{
    if (!filename.isEmpty())
        m_filename = filename;

    if (m_filename.isEmpty())
        throw LP::Error(tr("no filename specified"));

    QFile file(m_filename);
    if (!file.open(QIODevice::ReadOnly))
        throw LP::Error(file.errorString());

    clear();
    createRootItemIfNotPresent();
}

void MusicModel::setPluginManager(const PluginManager &pluginManager)
{
    m_pluginManager = pluginManager;
}


bool MusicModel::isIndexScore(const QModelIndex &index) const
{
    return indexHasItemType(index, ItemType::ScoreType);
}

bool MusicModel::isIndexTune(const QModelIndex &index) const
{
    return indexHasItemType(index, ItemType::TuneType);
}

bool MusicModel::isIndexPart(const QModelIndex &index) const
{
    return indexHasItemType(index, ItemType::PartType);
}

bool MusicModel::isIndexMeasure(const QModelIndex &index) const
{
    return indexHasItemType(index, ItemType::MeasureType);
}

bool MusicModel::isIndexSymbol(const QModelIndex &index) const
{
    return indexHasItemType(index, ItemType::SymbolType);
}

bool MusicModel::indexSupportsWritingOfData(const QModelIndex &index, int role) const
{
    if (MusicItem *item = itemForIndex(index)) {
        return item->itemSupportsWritingOfData(role);
    }
    return false;
}

bool MusicModel::indexHasItemType(const QModelIndex &index, LP::ItemType type) const
{
    if (MusicItem *item = itemForIndex(index)) {
        if (item->type() == type) {
            return true;
        }
    }
    return false;
}

void MusicModel::createRootItemIfNotPresent()
{
    if (!m_rootItem)
        m_rootItem = new RootItem();
}

bool MusicModel::isRowValid(MusicItem *item, int row) const
{
    if (row >= 0 &&
            row <= item->childCount()) {
        return true;
    }
    return false;
}

QModelIndex MusicModel::insertItem(const QString &text, const QModelIndex &parent, int row, MusicItem *item)
{
    return insertItems(text, parent, row, QList<MusicItem*>({item}));
}

QModelIndex MusicModel::insertItems(const QString &text, const QModelIndex &parent, int row,
                                    const QList<MusicItem*> &items)
{
    MusicItem *parentItem = itemForIndex(parent);
    if (!parentItem) {
        return QModelIndex();
    }

    bool okToInsert = true;
    foreach (const MusicItem *item, items) {
        if (!parentItem->okToInsertChild(item, row)) {
            okToInsert = false;
            break;
        }
    }

    if (!okToInsert) {
        qWarning() << "MusicModel: Can't insert items. Parent item returned false for "
                      "okToInsertChild for at least one item";
        return QModelIndex();
    }

    bool validRow = isRowValid(parentItem, row);
    if (validRow && okToInsert) {
        m_undoStack->push(new InsertItemsCommand(this, text,  parent, row, items));
        return index(row, 0, parent);
    } else {
        qWarning() << QString("MusicModel: Item can't be inserted into model: row valid (%1), okToInsert (%2)")
                      .arg(validRow)
                      .arg(okToInsert);
    }
    return QModelIndex();
}
