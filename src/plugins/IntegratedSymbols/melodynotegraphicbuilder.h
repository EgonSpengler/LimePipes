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

class QPixmap;
class QPainter;

class MelodyNoteGraphicBuilder : public SymbolGraphicBuilder
{
public:
    MelodyNoteGraphicBuilder();

    void updateSymbolGraphic(const QVariant &value, int key);
    QVector<int> graphicDataRoles() const;

private:
    QPixmap pixmapForActualItemData();
    QRectF rectForActualItemData();

    bool isPitchOnLine();

    void initSpaceBetweenNoteheadAndDots();
    void initSpaceBetweenDots();

    qreal yOffsetForNotehead(qreal pixmapHeight);
    qreal yOffsetForDots(qreal pixmapHeight);
    qreal xOffsetForDots();

    void addNotehead(QPainter *painter);
    void addDots(QPainter *painter);

    MusicFont::Glyph actualNoteheadGlyph();
};

#endif // MELODYNOTEGRAPHICBUILDER_H
