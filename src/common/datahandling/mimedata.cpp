/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QJsonDocument>
#include <QJsonObject>
#include <QMimeData>

#include "datakeys.h"
#include "mimedata.h"

static const int MaxCompression = 9;

using namespace LP;

QMimeData *MimeData::fromJsonArray(const QJsonArray &array)
{
    if (!array.count())
        return 0;

    QJsonObject firstElement = array.first().toObject();
    ItemType itemType = static_cast<ItemType>(firstElement.value(DataKey::ItemType).toInt());
    if (itemType == ItemType::NoItemType)
        return 0;

    QString mimeType = mimeTypeForItemType(itemType);
    if (mimeType.isEmpty())
        return 0;

    QJsonDocument jsonDoc;
    jsonDoc.setArray(array);

    QMimeData *mimeData = new QMimeData;
    QByteArray data = jsonDoc.toJson(QJsonDocument::Indented);
    mimeData->setData(mimeType, qCompress(data, MaxCompression));

    return mimeData;
}

QJsonArray MimeData::toJsonArray(QMimeData *mimeData)
{

}

QString MimeData::mimeTypeForItemType(LP::ItemType type)
{
    switch (type) {
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
