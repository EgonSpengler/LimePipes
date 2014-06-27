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

#include "musicmodel.h"
#include <QFile>
#include <QDebug>
#include <QMimeData>
#include <QPair>
#include <QString>
#include <QtWidgets/QUndoStack>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <commands/insertitemscommand.h>
#include <commands/removeitemscommand.h>
#include <rootitem.h>
#include <score.h>
#include <tune.h>
#include <part.h>
#include <measure.h>
#include <common/defines.h>
#include <common/datatypes/timesignature.h>
#include <utilities/error.h>

namespace {

const int MaxTuneUnderScore = 3;  //!< From limepipes.xsd
const int MaxCompression = 9;

}

QHash<int, QString> MusicModel::s_itemTypeTags = MusicModel::initItemTypeTags();

QHash<int, QString> MusicModel::initItemTypeTags()
{
    QHash<int, QString> typeTags;
    typeTags.insert(MusicItem::RootItemType, QString("LIMEPIPES"));
    typeTags.insert(MusicItem::ScoreType,    QString("SCORE"));
    typeTags.insert(MusicItem::TuneType,     QString("TUNE"));
    typeTags.insert(MusicItem::PartType,     QString("PART"));
    typeTags.insert(MusicItem::MeasureType,  QString("MEASURE"));
    typeTags.insert(MusicItem::SymbolType,   QString("SYMBOL"));
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

    QString mimeDataType;
    QMimeData *mimeData = new QMimeData();
    QByteArray xmlData;
    QXmlStreamWriter writer(&xmlData);

    writer.writeStartElement(s_itemTypeTags.value(MusicItem::RootItemType));
    foreach (QModelIndex index, indexes) {
        if (MusicItem *item = itemForIndex(index)) {
            if (mimeDataType.isEmpty())
                mimeDataType = mimeTypeForItem(item);

            writeMusicItemAndChildren(&writer, item);
        }
    }
    writer.writeEndElement();

    if (!mimeDataType.isEmpty()) {
        qDebug() << "Model mime data: " << xmlData;
        mimeData->setData(mimeDataType, qCompress(xmlData, MaxCompression));
        return mimeData;
    }
    return 0;
}

bool MusicModel::allModelIndexesHaveTheSameMusicItemType(const QModelIndexList &indexes) const
{
    int itemType = -1;
    MusicItem *item = 0;
    foreach (QModelIndex index, indexes) {
        item = itemForIndex(index);
        if (!item)
            return false;

        if (itemType == -1)
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
    case MusicItem::ScoreType:
        return LP::MimeTypes::Score;
    case MusicItem::TuneType:
        return LP::MimeTypes::Tune;
    case MusicItem::PartType:
        return LP::MimeTypes::Part;
    case MusicItem::MeasureType:
        return LP::MimeTypes::Measure;
    case MusicItem::SymbolType:
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
        QByteArray xmlData = qUncompress(mimeData->data(mimeType));
        QXmlStreamReader reader(xmlData);
        readMusicItems(&reader, &tempParentItem);

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
    case MusicItem::RootItemType:
        if (mimeType == LP::MimeTypes::Score)
            return true;
        return false;
    case MusicItem::ScoreType:
        if (mimeType == LP::MimeTypes::Tune)
            return true;
        return false;
    case MusicItem::TuneType:
        if (mimeType == LP::MimeTypes::Part)
            return true;
        return false;
    case MusicItem::PartType:
        if (mimeType == LP::MimeTypes::Measure)
            return true;
        return false;
    case MusicItem::MeasureType:
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
    Q_ASSERT(m_rootItem->childType() == MusicItem::ScoreType);

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

    InstrumentPtr instrument(m_pluginManager->instrumentForName(instrumentName));
    return insertItem("Insert tune into score", score, row, new Tune(instrument));
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
    InstrumentPtr instrument = data(tune, LP::TuneInstrument).value<InstrumentPtr>();
    if (instrument->type() == LP::NoInstrument)
        return QModelIndex();

    Part *newPart = new Part();
    newPart->setStaffType(instrument->staffType());
    newPart->setClefType(instrument->defaultClef());
    QModelIndex part = insertItem(tr("Insert part into tune"), tune, row, newPart);
    setData(part, QVariant::fromValue<bool>(withRepeat), LP::PartRepeat);
    for (int i=0; i<measures; i++) {
        Measure *measure = new Measure();
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
    if (!partItem && partItem->type() == MusicItem::PartType)
        return QModelIndex();

    QModelIndex tuneIndex = part.parent();
    Q_ASSERT(isIndexTune(tuneIndex));
    MusicItem *tuneItem = itemForIndex(tuneIndex);

    QVariant timeSigData = tuneItem->data(LP::TuneTimeSignature);
    if (!timeSigData.isValid() &&
            !timeSigData.canConvert<TimeSignature>())
        return QModelIndex();

    TimeSignature timeSig = timeSigData.value<TimeSignature>();
    Measure *measure = new Measure();
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
    if (!measureItem && measureItem->type() == MusicItem::MeasureType)
        return QModelIndex();

    QModelIndex tuneIndex = measure.parent().parent();
    Q_ASSERT(isIndexTune(tuneIndex));
    MusicItem *tuneItem = itemForIndex(tuneIndex);

    QVariant instrumentVar = tuneItem->data(LP::TuneInstrument);
    if (!instrumentVar.isValid() &&
            !instrumentVar.canConvert<InstrumentPtr>())
        return QModelIndex();

    InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
    Symbol *symbol = m_pluginManager->symbolForType(type);
    if (symbol == 0) {
        qWarning() << "MusicModel: Can't insert symbol. PluginManager returned 0 for symbol type "
                      << type;
        return QModelIndex();
    }

    SymbolCategory category = m_pluginManager->metaDataForSymbol(type).category();
    if (category == SymbolCategory::Spanning) {
        delete symbol;
        return insertSpanningSymbolIntoMeasure(row, measure, type);
    }

    // Init pitch and pitch context if symbol has it
    if (symbol->hasPitch()) {
        PitchContextPtr pitchContext = instrument->pitchContext();
        int initialStaffPos = 0;
        if (pitchContext->lowestStaffPos() > initialStaffPos) {
            initialStaffPos = pitchContext->lowestStaffPos();
        }
        PitchPtr pitch = pitchContext->pitchForStaffPos(initialStaffPos);
        QVariant pitchValue(QVariant::fromValue<PitchPtr>(pitch));
        symbol->setData(pitchValue, LP::SymbolPitch);
        QVariant pitchContextValue(QVariant::fromValue<PitchContextPtr>(pitchContext));
        symbol->setData(pitchContextValue, LP::SymbolPitchContext);
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

    Symbol *startSymbol = m_pluginManager->symbolForType(type);
    Symbol *endSymbol = m_pluginManager->symbolForType(type);
    if (startSymbol == 0 ||
            endSymbol == 0) {
        qWarning() << "MusicModel: Can't insert symbol. PluginManager returned 0 for symbol type "
                      << type;
        return QModelIndex();
    }

    startSymbol->setData(QVariant::fromValue<SymbolSpanType>(SymbolSpanType::Start),
                         LP::SymbolSpanType);
    endSymbol->setData(QVariant::fromValue<SymbolSpanType>(SymbolSpanType::End),
                         LP::SymbolSpanType);

    m_undoStack->beginMacro(tr("Insert %1 Items")
                            .arg(startSymbol->data(LP::SymbolName).toString()));
    QPersistentModelIndex endSymbolIndex = insertItem(QStringLiteral(""), measure, row, endSymbol);
    QPersistentModelIndex startSymbolIndex = insertItem(QStringLiteral(""), measure, row, startSymbol);
    setData(startSymbolIndex, QVariant(endSymbolIndex), LP::SymbolSpanBuddy);
    setData(endSymbolIndex, QVariant(startSymbolIndex), LP::SymbolSpanBuddy);
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

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writeMusicItemAndChildren(&writer, m_rootItem);
    writer.writeEndDocument();
}

void MusicModel::writeMusicItemAndChildren(QXmlStreamWriter *writer, MusicItem *musicItem) const
{
    if (!musicItem ||
            musicItem->type() == MusicItem::NoItemType)
        return;

    writer->writeStartElement(tagNameOfMusicItemType(musicItem->type()));

    if (musicItem->type() == MusicItem::RootItemType)
        writer->writeAttribute("VERSION", "0.1");
    if (musicItem->type() == MusicItem::TuneType)
        writeTuneAttributes(writer, musicItem);
    if (musicItem->type() == MusicItem::SymbolType)
        writeSymbolAttributes(writer, musicItem);

    musicItem->writeItemDataToXmlStream(writer);

    foreach (MusicItem *child, musicItem->children())
        writeMusicItemAndChildren(writer, child);

    writer->writeEndElement();
}

void MusicModel::writeTuneAttributes(QXmlStreamWriter *writer, MusicItem *musicItem) const
{
    QVariant instrumentVar = musicItem->data(LP::TuneInstrument);
    if (instrumentVar.isValid() &&
            instrumentVar.canConvert<InstrumentPtr>()) {
        InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
        writer->writeAttribute("INSTRUMENT", instrument->name());
    }
}

void MusicModel::writeSymbolAttributes(QXmlStreamWriter *writer, MusicItem *musicItem) const
{
    QVariant symbolTypeVar = musicItem->data(LP::SymbolType);
    if (symbolTypeVar.isValid() &&
            symbolTypeVar.canConvert<int>()) {
        writer->writeAttribute("TYPE", QString::number(symbolTypeVar.toInt()));
    }

    // Get instrument
    MusicItem *tuneItem = musicItem;
    InstrumentPtr instrument;
    while (1) {
        if (tuneItem->type() == MusicItem::ScoreType ||
                tuneItem->parent() == 0) {
            break;
        }

        if (tuneItem->type() == MusicItem::TuneType) {
            instrument = instrumentFromItem(tuneItem);
            break;
        }

        tuneItem = tuneItem->parent();
    }

    if (instrument.isNull()) {
        qWarning() << "Can't save instrument into symbol xml stream";
        return;
    }
    writer->writeAttribute("INSTRUMENT", instrument->name());
}

const QString MusicModel::tagNameOfMusicItemType(MusicItem::Type type) const
{
    return s_itemTypeTags.value(type);
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

    QXmlStreamReader reader(&file);
    readMusicItems(&reader, m_rootItem);
    if (reader.hasError())
        throw LP::Error(reader.errorString());
}

void MusicModel::setPluginManager(const PluginManager &pluginManager)
{
    m_pluginManager = pluginManager;
}

void MusicModel::readMusicItems(QXmlStreamReader *reader, MusicItem *item)
{
    while (!reader->atEnd()) {
        reader->readNext();
        if (reader->isStartElement()) {
            switch (item->type()) {
            case MusicItem::RootItemType:
                if (!isMusicItemTag(reader->name()))
                    throw LP::Error(tr("No valid LimePipes file"));

                processScoreTag(reader, &item);
                break;
            case MusicItem::ScoreType:
                processTuneTag(reader, &item);
                break;
            case MusicItem::TuneType:
                processPartTag(reader, &item);
                break;
            case MusicItem::PartType:
                processMeasureTag(reader, &item);
                break;
            case MusicItem::MeasureType:
                processSymbolTag(reader, &item);
                break;
            case MusicItem::SymbolType:
                readPitchIfSymbolHasPitch(reader, &item);
                item->readCurrentElementFromXmlStream(reader);
                break;
            case MusicItem::NoItemType:
                qWarning() << "An invalid music item can't be parent of anything.";
                break;
            }
        }
        if (reader->isEndElement() &&
                isEndTagOfCurrentItem(reader, item))
            item = item->parent();
    }
}

bool MusicModel::isMusicItemTag(const QString &tagName)
{
    return s_itemTypeTags.values().contains(tagName.toUpper());
}

bool MusicModel::isMusicItemTag(const QStringRef &tagName)
{
    return isMusicItemTag(QString().append(tagName));
}

void MusicModel::processScoreTag(QXmlStreamReader *reader, MusicItem **item)
{
    if (isValidScoreTag(reader))
        *item = itemPointerToNewChildItem<Score>(item);
    else
        (*item)->readCurrentElementFromXmlStream(reader);
}

bool MusicModel::isValidScoreTag(QXmlStreamReader *reader)
{
    return tagHasNameOfItemType(reader->name(), MusicItem::ScoreType);
}

bool MusicModel::tagHasNameOfItemType(QStringRef tagname, MusicItem::Type type)
{
    if (tagNameOfMusicItemType(type).compare(tagname, Qt::CaseInsensitive) == 0)
        return true;
    return false;
}

template<typename T>
T *MusicModel::itemPointerToNewChildItem(MusicItem **parent)
{
    return new T(*parent);
}

void MusicModel::processTuneTag(QXmlStreamReader *reader, MusicItem **item)
{
    if (isValidTuneTag(reader) &&
            (*item)->childCount() < MaxTuneUnderScore)
        *item = newTuneWithInstrument(reader, *item);
    else
        (*item)->readCurrentElementFromXmlStream(reader);
}

void MusicModel::processPartTag(QXmlStreamReader *reader, MusicItem **item)
{
    if (isValidPartTag(reader))
        *item = itemPointerToNewChildItem<Part>(item);
    else
        (*item)->readCurrentElementFromXmlStream(reader);
}

void MusicModel::processMeasureTag(QXmlStreamReader *reader, MusicItem **item)
{
    if (isValidMeasureTag(reader))
        *item = itemPointerToNewChildItem<Measure>(item);
    else
        (*item)->readCurrentElementFromXmlStream(reader);
}

bool MusicModel::isValidTuneTag(QXmlStreamReader *reader)
{
    if (tagHasNameOfItemType(reader->name(), MusicItem::TuneType) &&
            tagHasNonEmptyAttribute(reader, "INSTRUMENT") &&
            instrumentNameIsSupported(attributeValue(reader, "INSTRUMENT"))) {
        return true;
    }
    return false;
}

bool MusicModel::isValidPartTag(QXmlStreamReader *reader)
{
    return tagHasNameOfItemType(reader->name(), MusicItem::PartType);
}

bool MusicModel::isValidMeasureTag(QXmlStreamReader *reader)
{
    return tagHasNameOfItemType(reader->name(), MusicItem::MeasureType);
}

bool MusicModel::tagHasNonEmptyAttribute(QXmlStreamReader *reader, const QString &attributeName)
{
    if (!reader->attributes().hasAttribute(attributeName))
        return false;
    if (!reader->attributes().value(attributeName).isEmpty())
        return true;
    return false;
}

bool MusicModel::instrumentNameIsSupported(const QString &instrumentName)
{
    if (m_pluginManager.isNull()) {
        qWarning("No plugin manager installed. Can't check if instrument is supported.");
        return false;
    }

    if (m_pluginManager->instrumentNames().contains(instrumentName))
        return true;
    return false;
}

QString MusicModel::attributeValue(QXmlStreamReader *reader, const QString &attributeName)
{
    QString value;
    return value.append(reader->attributes().value(attributeName));
}

MusicItem *MusicModel::newTuneWithInstrument(QXmlStreamReader *reader, MusicItem *item)
{
    if (m_pluginManager.isNull()) {
        qWarning("No plugin manager installed. Can't return new tune with instrument.");
        return 0;
    }

    Tune *tune = itemPointerToNewChildItem<Tune>(&item);
    QString instrumentName = attributeValue(reader, "INSTRUMENT");
    tune->setInstrument(InstrumentPtr(m_pluginManager->instrumentForName(instrumentName)));
    return tune;
}

void MusicModel::processSymbolTag(QXmlStreamReader *reader, MusicItem **item)
{
    if (isValidSymbolTag(reader, *item))
        *item = newSymbolForMeasureItem(reader, *item);
    else
        (*item)->readCurrentElementFromXmlStream(reader);
}

void MusicModel::readPitchIfSymbolHasPitch(QXmlStreamReader *reader, MusicItem **item)
{
    Symbol *symbol = static_cast<Symbol*>(*item);
    if (!symbol)
        return;

    MusicItem *tuneItem = getTuneItemParent(*item);

    if (reader->name() == "PITCH" &&
            symbol->hasPitch()) {
        InstrumentPtr instrument = instrumentFromItem(tuneItem);
        if (instrument->type() == LP::NoInstrument)
            return;

        QStringList pitchNames(instrument->pitchContext()->pitchNames());
        QString readPitchName = reader->readElementText();
        if (pitchNames.contains(readPitchName)) {
            PitchPtr pitch = instrument->pitchContext()->pitchForName(readPitchName);
            (*item)->setData(QVariant::fromValue<PitchContextPtr>(instrument->pitchContext()),
                             LP::SymbolPitchContext);
            (*item)->setData(QVariant::fromValue<PitchPtr>(pitch), LP::SymbolPitch);
        }
    }
}

bool MusicModel::isValidSymbolTag(QXmlStreamReader *reader, MusicItem *item)
{
    MusicItem *tuneItem = getTuneItemParent(item);

    if (tagHasNameOfItemType(reader->name(), MusicItem::SymbolType) &&
            tagHasNonEmptyAttribute(reader, "TYPE") &&
            symbolTypeIsSupportedByTuneItem(reader, tuneItem)) {
        return true;
    }
    return false;
}

bool MusicModel::symbolTypeIsSupportedByTuneItem(QXmlStreamReader *reader, MusicItem *tuneItem)
{
    if (m_pluginManager.isNull()) {
        qWarning("No plugin manager installed. Can't check if symbol name is supported by tune item.");
        return false;
    }

    QString symbolTypeFromAttribute = attributeValue(reader, "TYPE");
    int symbolTypeAttribute = symbolTypeFromAttribute.toInt();

    InstrumentPtr instrument = instrumentFromItem(tuneItem);
    if (instrument->type() == LP::NoInstrument)
        return false;

    QVector<int> symbolTypes = m_pluginManager->symbolTypesForInstrument(instrument->name());

    if (symbolTypes.contains(symbolTypeAttribute)) {
            return true;
    }
    return false;
}

InstrumentPtr MusicModel::instrumentFromItem(MusicItem *item) const
{
    Q_ASSERT(item->type() == MusicItem::TuneType);

    QVariant instrumentVar = item->data(LP::TuneInstrument);
    if (instrumentVar.isValid() &&
            instrumentVar.canConvert<InstrumentPtr>()) {
        return instrumentVar.value<InstrumentPtr>();
    }
    return InstrumentPtr(new NullInstrument());
}

MusicItem *MusicModel::newSymbolForMeasureItem(QXmlStreamReader *reader, MusicItem *item)
{
    if (m_pluginManager.isNull()) {
        qWarning("No plugin manager installed. Can't return new symbol for measure item.");
        return 0;
    }

    MusicItem *tuneItem = getTuneItemParent(item);

    QString symbolTypeFromAttribute = attributeValue(reader, "TYPE");
    int symbolType = symbolTypeFromAttribute.toInt();

    InstrumentPtr instrument = instrumentFromItem(tuneItem);
    if (instrument->type() == LP::NoInstrument)
        return item;

    MusicItem *parent = item;
    MusicItem *child = m_pluginManager->symbolForType(symbolType);

    if (parent->okToInsertChild(child, parent->childCount()) &&
            parent->addChild(child)) {
        item = child;
    }
    else
        delete child;

    return item;
}

MusicItem *MusicModel::getTuneItemParent(MusicItem *item)
{
    Q_ASSERT(item);
    Q_ASSERT(item->parent());
    Q_ASSERT(item->type() != MusicItem::NoItemType);

    while (item->type() != MusicItem::TuneType) {
        item = item->parent();

        if (item->type() == MusicItem::RootItemType ||
                item->type() == MusicItem::ScoreType)
            break;
    }
    return item;
}

bool MusicModel::isEndTagOfCurrentItem(QXmlStreamReader *reader, MusicItem *item)
{
    if (isMusicItemTag(reader->name()) &&
            tagNameOfMusicItemType(item->type()).compare(reader->name(), Qt::CaseInsensitive) == 0) {
        return true;
    }
    return false;
}

bool MusicModel::isIndexScore(const QModelIndex &index) const
{
    return indexHasItemType(index, MusicItem::ScoreType);
}

bool MusicModel::isIndexTune(const QModelIndex &index) const
{
    return indexHasItemType(index, MusicItem::TuneType);
}

bool MusicModel::isIndexPart(const QModelIndex &index) const
{
    return indexHasItemType(index, MusicItem::PartType);
}

bool MusicModel::isIndexMeasure(const QModelIndex &index) const
{
    return indexHasItemType(index, MusicItem::MeasureType);
}

bool MusicModel::isIndexSymbol(const QModelIndex &index) const
{
    return indexHasItemType(index, MusicItem::SymbolType);
}

bool MusicModel::indexSupportsWritingOfData(const QModelIndex &index, int role) const
{
    if (MusicItem *item = itemForIndex(index)) {
        return item->itemSupportsWritingOfData(role);
    }
    return false;
}

bool MusicModel::indexHasItemType(const QModelIndex &index, MusicItem::Type type) const
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
