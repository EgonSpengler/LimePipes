/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTEGRAPHICBUILDER_H
#define MELODYNOTEGRAPHICBUILDER_H

#include <common/graphictypes/symbolgraphicbuilder.h>

class MelodyNoteGlyphItem;

class MelodyNoteGraphicBuilder : public SymbolGraphicBuilder
{
public:
    explicit MelodyNoteGraphicBuilder();

    void updateSymbolGraphic(const QVariant &value, int key);
    QVector<int> graphicDataRoles() const;
    GlyphItem *glyphItem() const;

private:
    QPixmap pixmapForActualItemData();

    bool isPitchOnLine();

    void initSpaceBetweenNoteheadAndDots();
    void initSpaceBetweenDots();

    MelodyNoteGlyphItem *m_glyph;

protected:
    void smuflChanged(const SMuFLPtr &smufl);
};

#endif // MELODYNOTEGRAPHICBUILDER_H
