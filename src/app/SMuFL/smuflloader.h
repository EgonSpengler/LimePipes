/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef SMUFLLOADER_H
#define SMUFLLOADER_H

#include <QObject>
#include <QJsonObject>
#include <QHash>
#include <QColor>
#include <common/graphictypes/MusicFont/musicfont.h>

class SMuFLLoader : public QObject,
                    public MusicFont
{
    Q_OBJECT
public:
    explicit SMuFLLoader(QObject *parent = 0);

    void setFont(const QFont &font);
    void setFontFromPath(const QString &path);
    void setFontPixelSize(int pixelSize);
    void setFontColor(const FontColor &colorType, const QColor& color);

    void loadGlyphnamesFromFile(const QString& glyphNamesFilePath);
    void loadFontMetadataFromFile(const QString& fontMetadataFilePath);

    QFont font() const;
    quint32 codepointForGlyph(const QString &glyphname) const;
    quint32 alternateCodepointForGlyph(const QString &glyphname) const;
    Engravings engravings() const;
    GlyphData glyphData(const QString &glyphname);
    QColor fontColor(const FontColor &color) const;

private:
    void setEngravings(const Engravings &engravings);
    void setEngravingsFromJson(const QJsonObject& json);
    GlyphData glyphDataFromJson(const QJsonObject& json);
    QPointF pointFromJsonValue(const QJsonObject& json, const QString& dataName);
    quint32 codepointFromString(const QString& codepoint) const;
    quint32 codepointFromGlyphAndCodepointType(const QString& glyphname, const QString &codepointType) const;
    QFont m_font;
    Engravings m_engravings;
    QJsonObject m_glyphNames;
    QJsonObject m_fontGlyphs;
    QHash<FontColor, QColor> m_fontColors;
};

#endif // SMUFLLOADER_H
