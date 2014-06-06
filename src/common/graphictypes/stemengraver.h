/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef STEMENGRAVER_H
#define STEMENGRAVER_H

#include <QList>

#include <common/graphictypes/MusicFont/musicfont.h>

class SymbolGraphicBuilder;
class StemGlyphItem;

struct StemData {
    StemData()
        : graphicBuilder(0),
          glyphItem(0)
    {}

    SymbolGraphicBuilder *graphicBuilder;
    StemGlyphItem *glyphItem;
};

class StemEngraver
{
public:
    explicit StemEngraver();
    virtual ~StemEngraver() {}

    void insertGraphicsBuilder(int index, SymbolGraphicBuilder *builder);

    void removeGraphicsBuilder(SymbolGraphicBuilder *builder);

    MusicFontPtr musicFont() const;
    void setMusicFont(const MusicFontPtr &musicFont);

private:
    void builderDataChanged(SymbolGraphicBuilder *builder, const QVariant &data, int role);
    StemData stemDataWithGraphicBuilder(SymbolGraphicBuilder *builder);
    QList<StemData> m_stemDatas;
    MusicFontPtr m_musicFont;
};

#endif // STEMENGRAVER_H
