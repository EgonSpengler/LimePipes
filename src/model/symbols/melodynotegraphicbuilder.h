/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTEGRAPHICBUILDER_H
#define MELODYNOTEGRAPHICBUILDER_H

#include <model/symbolgraphicbuilder.h>

class MelodyNoteGraphicBuilder : public SymbolGraphicBuilder
{
public:
    MelodyNoteGraphicBuilder(MusicItem *item);

    void createPixmaps(int lineHeight);
    void updateSymbolGraphic();
    bool isSymbolGraphicAffectedByDataRole(int role);

private:
    bool isPitchOnLine();
    bool itemHasRequiredData();
    void initSpaceBetweenGlyphs();
    void createNoteheads();
    void createDot();
    QPixmap pixmapForActualItemData();
    QRectF rectForActualItemData();
};

#endif // MELODYNOTEGRAPHICBUILDER_H
