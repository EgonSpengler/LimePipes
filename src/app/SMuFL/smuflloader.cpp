/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
#include <QFontDatabase>
#include <QDebug>
#include "smuflloader.h"

SMuFLLoader::SMuFLLoader(QObject *parent)
    : QObject(parent),
      m_engravings({0})
{
}

void SMuFLLoader::setFont(const QFont &font)
{
    m_font = font;
}

void SMuFLLoader::setFontFromPath(const QString &path)
{
    int fontId = QFontDatabase::addApplicationFont(path);
    if (fontId == -1) {
        qWarning() << QString("Font can't be added as application font: %1")
                      .arg(path);
        return;
    }

    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    if (!fontFamilies.count()) {
        qWarning() << QString("No application font family for id %1")
                      .arg(fontId);
        return;
    }

    m_font = QFont(fontFamilies.at(0));
}

void SMuFLLoader::setFontPixelSize(int pixelSize)
{
    m_font.setPixelSize(pixelSize);
}

void SMuFLLoader::loadGlyphnamesFromFile(const QString &glyphNamesFilePath)
{
    QFile glyphNamesFile(glyphNamesFilePath);
    glyphNamesFile.open(QIODevice::ReadOnly);
    QJsonDocument smuflGlyphMeta(QJsonDocument::fromJson(glyphNamesFile.readAll()));
    glyphNamesFile.close();

    QJsonObject smuflGlyphs(smuflGlyphMeta.object());
    if (smuflGlyphs.isEmpty()) {
        qWarning() << QString("File %1 contains no Json object").arg(glyphNamesFilePath);
        return;
    }

    m_glyphNames = smuflGlyphs;
}

void SMuFLLoader::loadFontMetadataFromFile(const QString &fontMetadataFilePath)
{
    QFile fontMetadataFile(fontMetadataFilePath);
    fontMetadataFile.open(QIODevice::ReadOnly);
    QJsonDocument smuflGlyphMeta(QJsonDocument::fromJson(fontMetadataFile.readAll()));
    fontMetadataFile.close();

    QJsonObject fontMetaData(smuflGlyphMeta.object());
    if (fontMetaData.isEmpty()) {
        qWarning() << QString("File %1 contains no Json object").arg(fontMetadataFilePath);
        return;
    }

    QJsonObject engravingsJson(fontMetaData.value(QStringLiteral("engravingDefaults")).toObject());
    if (engravingsJson.isEmpty())
        return;

    setEngravingsFromJson(engravingsJson);

    m_fontGlyphs = fontMetaData.value(QStringLiteral("glyphs")).toObject();
}

void SMuFLLoader::setInstance(SMuFL *smuflInstance)
{
    m_smufl = smuflInstance;
}

void SMuFLLoader::setEngravingsFromJson(const QJsonObject &json)
{
    Engravings newEngravings{0};
    newEngravings.arrowShaftThickness = json.value(QStringLiteral("arrowShaftThickness")).toDouble();
    newEngravings.barlineSeparation = json.value(QStringLiteral("barlineSeparation")).toDouble();
    newEngravings.beamSpacing = json.value(QStringLiteral("beamSpacing")).toDouble();
    newEngravings.beamThickness = json.value(QStringLiteral("beamThickness")).toDouble();
    newEngravings.bracketThickness = json.value(QStringLiteral("bracketThickness")).toDouble();
    newEngravings.dashedBarlineDashLength = json.value(QStringLiteral("dashedBarlineDashLength")).toDouble();
    newEngravings.dashedBarlineGapLength = json.value(QStringLiteral("dashedBarlineGapLength")).toDouble();
    newEngravings.dashedBarlineThickness = json.value(QStringLiteral("dashedBarlineThickness")).toDouble();
    newEngravings.hairpinThickness = json.value(QStringLiteral("hairpinThickness")).toDouble();
    newEngravings.legerLineExtension = json.value(QStringLiteral("legerLineExtension")).toDouble();
    newEngravings.legerLineThickness = json.value(QStringLiteral("legerLineThickness")).toDouble();
    newEngravings.lyricLineThickness = json.value(QStringLiteral("lyricLineThickness")).toDouble();
    newEngravings.octaveLineThickness = json.value(QStringLiteral("octaveLineThickness")).toDouble();
    newEngravings.pedalLineThickness = json.value(QStringLiteral("pedalLineThickness")).toDouble();
    newEngravings.repeatBarlineDotSeparation = json.value(QStringLiteral("repeatBarlineDotSeparation")).toDouble();
    newEngravings.repeatEndingLineThickness = json.value(QStringLiteral("repeatEndingLineThickness")).toDouble();
    newEngravings.slurEndpointThickness = json.value(QStringLiteral("slurEndpointThickness")).toDouble();
    newEngravings.slurMidpointThickness = json.value(QStringLiteral("slurMidpointThickness")).toDouble();
    newEngravings.staffLineThickness = json.value(QStringLiteral("staffLineThickness")).toDouble();
    newEngravings.stemThickness = json.value(QStringLiteral("stemThickness")).toDouble();
    newEngravings.subBracketThickness = json.value(QStringLiteral("subBracketThickness")).toDouble();
    newEngravings.textEnclosureThickness = json.value(QStringLiteral("textEnclosureThickness")).toDouble();
    newEngravings.thickBarlineThickness = json.value(QStringLiteral("thickBarlineThickness")).toDouble();
    newEngravings.thinBarlineThickness = json.value(QStringLiteral("thinBarlineThickness")).toDouble();
    newEngravings.tieEndpointThickness = json.value(QStringLiteral("tieEndpointThickness")).toDouble();
    newEngravings.tieMidpointThickness = json.value(QStringLiteral("tieMidpointThickness")).toDouble();
    newEngravings.tupletBracketThickness = json.value(QStringLiteral("tupletBracketThickness")).toDouble();

    m_engravings = newEngravings;
}

QFont SMuFLLoader::font() const
{
    return m_font;
}

quint32 SMuFLLoader::codepointForGlyph(const QString &glyphname) const
{
    return codepointFromGlyphAndCodepointType(glyphname, QStringLiteral("codepoint"));
}

quint32 SMuFLLoader::alternateCodepointForGlyph(const QString &glyphname) const
{
    return codepointFromGlyphAndCodepointType(glyphname, QStringLiteral("alternateCodepoint"));
}

quint32 SMuFLLoader::codepointFromGlyphAndCodepointType(const QString &glyphname, const QString& codepointType) const
{
    QJsonObject glyphdata(m_glyphNames.value(glyphname).toObject());
    if (glyphdata.isEmpty())
        return 0;

    QString codepoint = glyphdata.value(codepointType).toString();
    if (codepoint.isEmpty())
        return 0;

    return codepointFromString(codepoint);
}

Engravings SMuFLLoader::engravings() const
{
    return m_engravings;
}

GlyphData SMuFLLoader::glyphData(const QString &glyphname)
{
    GlyphData data;
    QJsonObject glyphDataJson(m_fontGlyphs.value(glyphname).toObject());
    if (glyphDataJson.isEmpty())
        return data;

    data = glyphDataFromJson(glyphDataJson);

    return data;
}

GlyphData SMuFLLoader::glyphDataFromJson(const QJsonObject &json)
{
    GlyphData data;
    data.nominalWidth = static_cast<qreal>(json.value(QStringLiteral("nominalWidth")).toDouble());
    data.numeralBottom = pointFromJsonValue(json, QStringLiteral("numeralBottom"));
    data.numeralTop = pointFromJsonValue(json, QStringLiteral("numeralTop"));
    data.stemDownNW = pointFromJsonValue(json, QStringLiteral("stemDownNW"));
    data.stemDownSW = pointFromJsonValue(json, QStringLiteral("stemDownSW"));
    data.stemUpNW = pointFromJsonValue(json, QStringLiteral("stemUpNW"));
    data.stemUpSE = pointFromJsonValue(json, QStringLiteral("stemUpSE"));

    return data;
}

QPointF SMuFLLoader::pointFromJsonValue(const QJsonObject &json, const QString &dataName)
{
    QJsonArray pointArray = json.value(dataName).toArray();
    if (pointArray.isEmpty())
        return QPointF();

    if (pointArray.count() != 2)
        return QPointF();

    QPointF point(pointArray.at(0).toDouble(), pointArray.at(1).toDouble());
    return point;
}

quint32 SMuFLLoader::codepointFromString(const QString &codepoint) const
{
    if (codepoint.isEmpty())
        return 0;

    QString point(codepoint);
    point = point.replace(QLatin1String("U+"), QLatin1String("0x"));

    bool ok;
    quint32 code = point.toUInt(&ok, 16);

    if (!ok)
        return 0;

    return code;
}
