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

QJsonArray MimeData::toJsonArray(const QMimeData *mimeData)
{
    QString mimeType = supportedMimeTypeFromData(mimeData);
    if (mimeType.isEmpty())
        return QJsonArray();

    QByteArray data = qUncompress(mimeData->data(mimeType));
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = jsonDoc.array();

    return jsonArray;
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

/*!
 * \brief MimeData::supportedMimeTypeFromData Returns the first mime type from QMimeData,
 *        which is supported by LimePipes
 * \param data The mime data to check for supported mime type
 * \return The supported mime type or an empty string, if no supported mime type can be found.
 */
QString MimeData::supportedMimeTypeFromData(const QMimeData *data)
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
