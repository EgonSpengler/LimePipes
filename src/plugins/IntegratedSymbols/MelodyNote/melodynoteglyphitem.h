/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MELODYNOTEGLYPHITEM_H
#define MELODYNOTEGLYPHITEM_H

#include <QVector>
#include <QGraphicsLineItem>
#include <common/graphictypes/glyphitem.h>
#include <common/datatypes/length.h>

class MelodyNoteGlyphItem : public GlyphItem
{
public:
    explicit MelodyNoteGlyphItem();

    void setLength(Length::Value length);

    void setNoteIsOnLine(bool onLine);

    void setDots(int dots);

    void setLedgerLines(int count, bool aboveNotehead);

    QPen ledgerLinePen() const;

    QString glyphName() const;
    GlyphData itemGlyphData() const;

protected:
    void musicFontHasChanged(const MusicFontPtr &musicFont);
    void colorRoleHasChanged(const FontColor &color);

private:
    enum class LedgerLinePosition {
        Above,
        Below
    };

    QString noteheadForLength(Length::Value length);
    void setAugmentationDots(int dotCount);
    void setDotGlyphCount(int dotCount);
    void setLedgerLinesItems(int count);
    void layoutNoteHead();
    void layoutLedgerLineItems();
    void layoutAugmentationDots();
    qreal spaceBetweenNoteheadAndDot() const;
    qreal spaceBetweenAugmentationDots() const;
    qreal augmentationPositionAboveLine() const;
    bool hasLedgerLines() const;
    qreal ledgerLineExtensionWidth() const;
    GlyphItem *m_notehead;
    QVector<GlyphItem*> m_augmentationDots;
    QVector<QGraphicsLineItem*> m_ledgerLines;
    LedgerLinePosition m_ledgerPosition;
    bool m_onLine;
};

#endif // MELODYNOTEGLYPHITEM_H
