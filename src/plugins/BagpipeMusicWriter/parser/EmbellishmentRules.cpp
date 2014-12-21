/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QDir>
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include "EmbellishmentRules.h"

EmbellishmentRules::EmbellishmentRules(QObject *parent) :
    QObject(parent)
{
}

void EmbellishmentRules::addRulesFromDirectory(const QDir &directory)
{
    QFileInfoList jsonFiles = directory.entryInfoList(QStringList() << "*.json",
                                                      QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    foreach (const QFileInfo fileInfo, jsonFiles) {
        addRulesFromFile(fileInfo.absoluteFilePath());
    }
}

QList<SymbolPitch> EmbellishmentRules::getAppearanceForEmbellishment(const Embellishment &embellishment)
{
    QList<SymbolPitch> pitches;

    return pitches;
}

void EmbellishmentRules::addRulesFromFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &jsonError);
    file.close();

    if (jsonError.error != QJsonParseError::NoError) {
        qWarning() << "Failed parsing embellishment rule file " << fileName
                   << " at " << jsonError.offset
                   << ": " << jsonError.errorString();
        return;
    }

    QJsonObject fileObject = jsonDoc.object();
    if (fileObject.isEmpty()) {
        return;
    }

    foreach (const QString &embellishmentType, fileObject.keys()) {
        QJsonObject embellishmentObject = fileObject.value(embellishmentType).toObject();
        foreach (const QString &embellishmentVariant, embellishmentObject.keys()) {
            QJsonObject variantObject = embellishmentObject.value(embellishmentVariant).toObject();
            if (!variantObject.isEmpty()) {
                qDebug() << "Found " << embellishmentType << QString("(%1)").arg(embellishmentVariant);
            }
        }
    }
}
