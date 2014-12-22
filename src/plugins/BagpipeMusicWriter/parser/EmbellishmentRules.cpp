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
    m_typeMapping = initTypeMapping();
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

    if (embellishment.embellishmentType() == Embellishment::SINGLE_GRACE) {
        pitches << embellishment.pitchHint();
        return pitches;
    }

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
            if (variantObject.isEmpty()) {
                continue;
            }

            QPair<QString, QString> embellishmentKey = qMakePair(embellishmentType, embellishmentVariant);
            if (!m_typeMapping.contains(embellishmentKey)) {
                qWarning() << QString("No mapping for %1 (%2)").arg(embellishmentType)
                              .arg(embellishmentVariant);
                return;
            }

            Embellishment::Type type = m_typeMapping.value(embellishmentKey);

            foreach (const QString &ruleName, variantObject.keys()) {
                QJsonObject ruleObject = variantObject.value(ruleName).toObject();
                qDebug() << "Rule: " << ruleName;
            }

            qDebug() << "Found " << embellishmentType << QString("(%1)").arg(embellishmentVariant);
        }
    }
}

QHash<QPair<QString, QString>, Embellishment::Type> EmbellishmentRules::initTypeMapping()
{
    QHash<QPair<QString, QString>, Embellishment::Type> mapping;
    mapping.insert(qMakePair(QStringLiteral("single grace"), QStringLiteral("single grace")), Embellishment::SINGLE_GRACE);
    mapping.insert(qMakePair(QStringLiteral("doubling"), QStringLiteral("half")), Embellishment::DOUBLING_HALF);
    mapping.insert(qMakePair(QStringLiteral("doubling"), QStringLiteral("regular")), Embellishment::DOUBLING_REG);
    mapping.insert(qMakePair(QStringLiteral("grip"), QStringLiteral("b")), Embellishment::GRIP_B);
    mapping.insert(qMakePair(QStringLiteral("grip"), QStringLiteral("g")), Embellishment::GRIP_G);
    mapping.insert(qMakePair(QStringLiteral("grip"), QStringLiteral("half")), Embellishment::GRIP_HALF);
    mapping.insert(qMakePair(QStringLiteral("grip"), QStringLiteral("long")), Embellishment::GRIP_LONG);
    mapping.insert(qMakePair(QStringLiteral("grip"), QStringLiteral("regular")), Embellishment::GRIP_REG);
    mapping.insert(qMakePair(QStringLiteral("grip"), QStringLiteral("thumb")), Embellishment::GRIP_THUMB);
    return mapping;
}
