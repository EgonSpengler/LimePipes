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
 */

#include "musicmodel.h"
#include <QXmlStreamWriter>
#include <rootitem.h>
#include <score.h>
#include <tune.h>
#include <utilities/error.h>

namespace {

const QString ScoreTag("SCORE");
const QString TuneTag("TUNE");
const QString SymbolTag("SYMBOL");

}

MusicModel::MusicModel(QObject *parent)
    : QAbstractItemModel(parent), m_rootItem(0), m_columnCount(1)
{
    m_instrumentManager = new InstrumentManager(pluginsDir());
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
        theFlags |= Qt::ItemIsSelectable |
                    Qt::ItemIsEnabled |
                    Qt::ItemIsEditable;
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

QModelIndex MusicModel::insertScore(int row, const QString &title)
{
    createRootItemIfNotPresent();
    Q_ASSERT(m_rootItem->childType() == MusicItem::ScoreType);

    return insertItem(row, QModelIndex(), new Score(title));
}

QModelIndex MusicModel::appendScore(const QString &title)
{
    createRootItemIfNotPresent();
    return insertScore(m_rootItem->childCount(), title);
}

QModelIndex MusicModel::insertTuneIntoScore(int row, const QModelIndex &score, const QString &instrumentName)
{
    InstrumentPtr instrument = m_instrumentManager->instrumentForName(instrumentName);
    return insertItem(row, score, new Tune(instrument));
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
    QModelIndex score = insertScore(rowOfScore, scoreTitle);
    return insertTuneIntoScore(0, score, instrumentName);
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

    return insertItem(row, tune, symbol);
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
    writer.writeStartElement("LIMEPIPES");
    writer.writeAttribute("VERSION", "0.1");
    writeMusicItemAndChildren(&writer, m_rootItem);
    writer.writeEndElement(); // LIMEPIPES
    writer.writeEndDocument();
}

void MusicModel::writeMusicItemAndChildren(QXmlStreamWriter *writer, MusicItem *musicItem) const
{
    if (musicItem->type() == MusicItem::NoItemType)
        return;

    if (musicItem->type() != MusicItem::RootItemType)
        writer->writeStartElement(tagNameFromItem(musicItem));

    musicItem->writeItemDataToXmlStream(writer);

    foreach (MusicItem *child, musicItem->children())
        writeMusicItemAndChildren(writer, child);

    if (musicItem->type() != MusicItem::RootItemType)
        writer->writeEndElement();
}

const QString MusicModel::tagNameFromItem(MusicItem *musicItem) const
{
    switch (musicItem->type()) {
    case MusicItem::ScoreType:
        return ScoreTag;
    case MusicItem::TuneType:
        return TuneTag;
    case MusicItem::SymbolType:
        return SymbolTag;
    default:
        return "";
    }
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

QModelIndex MusicModel::insertItem(int row, const QModelIndex &parent, MusicItem *item)
{
    if (MusicItem *parentItem = itemForIndex(parent)) {
        if (isRowValid(parentItem, row) && parentItem->okToInsertChild(item)) {
            beginInsertRows(parent, row, row);
            parentItem->insertChild(row, item);
            endInsertRows();
            return index(row, 0, parent);
        }
    }
    return QModelIndex();
}
