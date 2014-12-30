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
#include <QStringList>
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

QList<SymbolPitch> EmbellishmentRules::appearanceForEmbellishment(const Embellishment &embellishment)
{
    if (embellishment.precedingPitch() == NoPitch ||
            embellishment.followingPitch() == NoPitch) {
        qWarning() << "EmbellishmentRules::appearanceForEmbellishment: "
                      "Embellishment has no preceeding and/or following pitch: "
                   << embellishment;
        return QList<SymbolPitch>();
    }

    EmbellishmentRule rule = embellishmentRuleForEmbellishment(embellishment);
    if (rule.isEmpty()) {
        qWarning() << "No rule for embellishment " << embellishment;
        return QList<SymbolPitch>();
    } else {
        return rule.appearance();
    }
}

EmbellishmentRule EmbellishmentRules::embellishmentRuleForEmbellishment(const Embellishment &embellishment)
{
    Embellishment::Type type = embellishment.embellishmentType();
    if (type == Embellishment::NO_TYPE) {
        return EmbellishmentRule();
    }

    const QList<EmbellishmentRule> rules = m_rules.values(type);
    QList<EmbellishmentRule> validRules;
    foreach (const EmbellishmentRule &rule, rules) {
        if (rule.isValidFor(embellishment.precedingPitch(), embellishment.followingPitch())) {
            validRules << rule;
        }
    }

    EmbellishmentRule selectedRule;
    if (validRules.count() > 1) {
        selectedRule = selectRuleForEmbellishment(embellishment, validRules);
        return selectedRule;
    }

    if (validRules.count() == 1) {
        selectedRule = validRules.first();
    }

    return selectedRule;
}

EmbellishmentRule EmbellishmentRules::selectRuleForEmbellishment(const Embellishment &embellishment,
                                                                 const QList<EmbellishmentRule> &rules)
{
    if (embellishment.embellishmentType() == Embellishment::SINGLE_GRACE) {
        // Pitch hint == embellishment rule appearanct (one note)
        foreach (const EmbellishmentRule &rule, rules) {
            if (rule.appearance().contains(embellishment.pitchHint())) {
                return rule;
            }
        }
        qDebug() << "No rule found for single grace: " << embellishment;
    }

    if (rules.count() > 0) {
        return rules.at(0);
    }

    return EmbellishmentRule();
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

    // Embellishment types
    foreach (const QString &embellishmentType, fileObject.keys()) {
        QJsonObject embellishmentObject = fileObject.value(embellishmentType).toObject();

        // Embellish variant
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

            qDebug() << "Embellishment " << embellishmentType << QString(" (%1)").arg(embellishmentVariant);
            // Embellishment rules
            foreach (const QString &ruleName, variantObject.keys()) {
                QJsonObject ruleObject = variantObject.value(ruleName).toObject();
                if (ruleObject.isEmpty()) {
                    continue;
                }

                EmbellishmentRule rule = ruleFromJsonObject(ruleName, ruleObject);

                if (!rule.isEmpty()) {
                    m_rules.insertMulti(type, rule);
                }
            }
        }
    }
}

EmbellishmentRule EmbellishmentRules::ruleFromJsonObject(const QString &name, const QJsonObject &json)
{
    EmbellishmentRule rule;
    rule.setName(name);
    QJsonArray appearanceArray = json.value(QStringLiteral("appearance")).toArray();
    rule.setAppearance(appearanceFromJsonArray(appearanceArray));
    QJsonObject rulesObject = json.value(QStringLiteral("following")).toObject();
    foreach (const QString &ruleKey, rulesObject.keys()) {
        PitchRange followingRange = pitchRangeFromString(ruleKey);
        if (!followingRange.isValid()) {
            continue;
        }

        QJsonObject followingRule = rulesObject.value(ruleKey).toObject();
        QString validPreceedingString = followingRule.value(QStringLiteral("valid_preceding")).toString();
        if (validPreceedingString.isEmpty()) {
            continue;
        }

        PitchRange validPreceedingRange = pitchRangeFromString(validPreceedingString);
        if (!validPreceedingRange.isValid()) {
            continue;
        }

        rule.addValidCombination(validPreceedingRange, followingRange);
    }

    return rule;
}

QList<SymbolPitch> EmbellishmentRules::appearanceFromJsonArray(const QJsonArray &array)
{
    QList<SymbolPitch> appearance;
    auto it = array.constBegin();
    while (it != array.constEnd()) {
        SymbolPitch pitch = pitchFromString((*it).toString());
        appearance << pitch;
        ++it;
    }

    return appearance;
}

PitchRange EmbellishmentRules::pitchRangeFromString(const QString &rangeString)
{
    PitchRange range;

    // A real range with start and end ...
    if (rangeString.contains(QStringLiteral("-"))) {
        QStringList rangeParts = rangeString.split(QStringLiteral("-"));
        if (!rangeParts.count() == 2) {
            qWarning() << "Pitch range " << rangeString << " contains more than one -";
            return range;
        }

        SymbolPitch firstPitch = pitchFromString(rangeParts.first());
        SymbolPitch secondPitch = pitchFromString(rangeParts.last());
        if (!PitchRange::checkPitchRange(firstPitch, secondPitch)) {
            qWarning() << "No valid pitch range: " << rangeString;
            return range;
        }

        range.setStartPitch(firstPitch);
        range.setEndPitch(secondPitch);
    } else {
        // No range, only a single pitch
        SymbolPitch pitch = pitchFromString(rangeString);
        if (pitch != NoPitch) {
            range.setStartPitch(pitch);
            range.setEndPitch(pitch);
        }
    }

    return range;
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
