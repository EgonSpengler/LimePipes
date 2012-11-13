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
#include <QDebug>
#include <QMimeData>
#include <QUndoStack>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <commands/insertitemscommand.h>
#include <commands/removeitemscommand.h>
#include <rootitem.h>
#include <score.h>
#include <tune.h>
#include <utilities/error.h>

namespace {

const int MaxCompression = 9;
const QString ScoreMimeType  = "application/vnd.limepipes.xml.score.z";
const QString TuneMimeType   = "application/vnd.limepipes.xml.tune.z";
const QString SymbolMimeType = "application/vnd.limepipes.xml.symbol.z";

}

QHash<int, QString> MusicModel::s_itemTypeTags = initItemTypeTags();

QHash<int, QString> MusicModel::initItemTypeTags()
{
    QHash<int, QString> typeTags;
    typeTags.insert(MusicItem::RootItemType, QString("LIMEPIPES"));
    typeTags.insert(MusicItem::ScoreType, QString("SCORE"));
    typeTags.insert(MusicItem::TuneType, QString("TUNE"));
    typeTags.insert(MusicItem::SymbolType, QString("SYMBOL"));
    return typeTags;
}

MusicModel::MusicModel(QObject *parent)
    : QAbstractItemModel(parent), m_rootItem(0), m_columnCount(1),
      m_dropMimeDataOccured(false)
{
    m_instrumentManager = new InstrumentManager(pluginsDir());
    m_undoStack = new QUndoStack(this);
}

MusicModel::~MusicModel()
{
    delete m_rootItem;
    delete m_instrumentManager;
}

QDir MusicModel::pluginsDir()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    return pluginsDir;
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
        item->setData(value, role);
        return true;
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
    return QStringList() << ScoreMimeType << TuneMimeType << SymbolMimeType;
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
        return ScoreMimeType;
    case MusicItem::TuneType:
        return TuneMimeType;
    case MusicItem::SymbolType:
        return SymbolMimeType;
    default:
        return QString();
    }
}

bool MusicModel::dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (action == Qt::IgnoreAction)
        return true;

    if (action != Qt::MoveAction || column > 0 ||
            !mimeData || !dataHasSupportedMimeType(mimeData))
        return false;

    Q_ASSERT(mimeData->formats().count() == 1);
    QString mimeType = mimeData->formats().at(0);

    createRootItemIfNotPresent();
    if (MusicItem *parentItem = itemForIndex(parent)) {
        if (!itemSupportsDropOfMimeType(parentItem, mimeType))
            return false;

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

bool MusicModel::dataHasSupportedMimeType(const QMimeData *data)
{
    if (data->hasFormat(ScoreMimeType) ||
            data->hasFormat(TuneMimeType) ||
            data->hasFormat(SymbolMimeType))
        return true;
    return false;
}

bool MusicModel::itemSupportsDropOfMimeType(const MusicItem *item, const QString &mimeType)
{
    switch(item->type()) {
    case MusicItem::RootItemType:
        if (mimeType == ScoreMimeType)
            return true;
        return false;
    case MusicItem::ScoreType:
        if (mimeType == TuneMimeType)
            return true;
        return false;
    case MusicItem::TuneType:
        if (mimeType == SymbolMimeType)
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

    return insertItem("Insert score", QModelIndex(), row, new Score(title));
}

QModelIndex MusicModel::appendScore(const QString &title)
{
    createRootItemIfNotPresent();
    return insertScore(m_rootItem->childCount(), title);
}

QModelIndex MusicModel::insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName)
{
    InstrumentPtr instrument = m_instrumentManager->instrumentForName(instrumentName);
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

QModelIndex MusicModel::insertSymbol(int row, const QModelIndex &tune, const QString &symbolName)
{
    MusicItem *tuneItem = itemForIndex(tune);
    if (!tuneItem)
        return QModelIndex();

    QVariant instrumentVar = tuneItem->data(LP::tuneInstrument);
    if (!instrumentVar.isValid() &&
            !instrumentVar.canConvert<InstrumentPtr>())
        return QModelIndex();

    InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
    Symbol *symbol = m_instrumentManager->symbolForName(instrument->name(), symbolName);

    if (symbol &&
            symbol->symbolType() == LP::NoSymbolType)
        return QModelIndex();
    QString insertText = tr("Insert %1").arg(symbol->data(LP::symbolName).toString());

    return insertItem(insertText, tune, row, symbol);
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

void MusicModel::clear()
{
    delete m_rootItem;
    m_rootItem = 0;
    reset();
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
    QVariant instrumentVar = musicItem->data(LP::tuneInstrument);
    if (instrumentVar.isValid() &&
            instrumentVar.canConvert<InstrumentPtr>()) {
        InstrumentPtr instrument = instrumentVar.value<InstrumentPtr>();
        writer->writeAttribute("INSTRUMENT", instrument->name());
    }
}

void MusicModel::writeSymbolAttributes(QXmlStreamWriter *writer, MusicItem *musicItem) const
{
    QVariant symbolNameVar = musicItem->data(LP::symbolName);
    if (symbolNameVar.isValid() &&
            symbolNameVar.canConvert<QString>()) {
        writer->writeAttribute("NAME", symbolNameVar.toString());
    }
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

    reset();
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
    if (isValidTuneTag(reader))
        *item = newTuneWithInstrument(reader, *item);
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
    if (m_instrumentManager->instrumentNames().contains(instrumentName))
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
    Tune *tune = itemPointerToNewChildItem<Tune>(&item);
    QString instrumentName = attributeValue(reader, "INSTRUMENT");
    tune->setInstrument(m_instrumentManager->instrumentForName(instrumentName));
    return tune;
}

void MusicModel::processSymbolTag(QXmlStreamReader *reader, MusicItem **item)
{
    if (isValidSymbolTag(reader, *item))
        *item = newSymbolForTuneItem(reader, *item);
    else
        (*item)->readCurrentElementFromXmlStream(reader);
}

void MusicModel::readPitchIfSymbolHasPitch(QXmlStreamReader *reader, MusicItem **item)
{
    Symbol *symbol = static_cast<Symbol*>(*item);
    if (!symbol)
        return;

    if (reader->name() == "PITCH" &&
            symbol->hasPitch()) {
        InstrumentPtr instrument = instrumentFromItem((*item)->parent());
        if (instrument->type() == LP::NoInstrument)
            return;

        QStringList pitchNames(instrument->pitchContext()->pitchNames());
        QString readPitchName = reader->readElementText();
        if (pitchNames.contains(readPitchName)) {
            PitchPtr pitch = instrument->pitchContext()->pitchForName(readPitchName);
            (*item)->setData(QVariant::fromValue<PitchPtr>(pitch), LP::symbolPitch);
        }
    }
}

bool MusicModel::isValidSymbolTag(QXmlStreamReader *reader, MusicItem *item)
{
    if (tagHasNameOfItemType(reader->name(), MusicItem::SymbolType) &&
            tagHasNonEmptyAttribute(reader, "NAME") &&
            symbolNameIsSupported(reader, item)) {
        return true;
    }
    return false;
}

bool MusicModel::symbolNameIsSupported(QXmlStreamReader *reader, MusicItem *tuneItem)
{
    QString symbolNameFromAttribute = attributeValue(reader, "NAME");

    InstrumentPtr instrument = instrumentFromItem(tuneItem);
    if (instrument->type() == LP::NoInstrument)
        return false;

    QStringList symbolNames =
            m_instrumentManager->symbolNamesForInstrument(instrument->name());

    if (symbolNames.contains(symbolNameFromAttribute)) {
        return true;
    }
    return false;
}

InstrumentPtr MusicModel::instrumentFromItem(MusicItem *item)
{
    QVariant instrumentVar = item->data(LP::tuneInstrument);
    if (instrumentVar.isValid() &&
            instrumentVar.canConvert<InstrumentPtr>()) {
        return instrumentVar.value<InstrumentPtr>();
    }
    return InstrumentPtr(new NullInstrument());
}

MusicItem *MusicModel::newSymbolForTuneItem(QXmlStreamReader *reader, MusicItem *item)
{
    QString symbolNameFromAttribute = attributeValue(reader, "NAME");

    InstrumentPtr instrument = instrumentFromItem(item);
    if (instrument->type() == LP::NoInstrument)
        return item;

    MusicItem *parent = item;
    item = m_instrumentManager->symbolForName(instrument->name(), symbolNameFromAttribute);
    parent->addChild(item);
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
    if (MusicItem *parentItem = itemForIndex(parent)) {
        if (isRowValid(parentItem, row) && parentItem->okToInsertChild(item, row)) {
            m_undoStack->push(new InsertItemsCommand(this, text,  parent, row, QList<MusicItem*>() << item));
            return index(row, 0, parent);
        }
    }
    return QModelIndex();
}
