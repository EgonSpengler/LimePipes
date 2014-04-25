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
#include <common/graphictypes/glyphitem.h>
#include <common/datatypes/length.h>

class MelodyNoteGlyphItem : public GlyphItem
{
public:
    explicit MelodyNoteGlyphItem();

    void setLength(Length::Value length);

    void setNoteIsOnLine(bool onLine);

    void setDots(int dots);

    // GlyphItem interface
    void setDotGlyphCount(int dotCount);
protected:
    void smuflHasChanged(const SMuFLPtr &smufl);

private:
    QString noteheadForLength(Length::Value length);
    void setAugmentationDots(int dotCount);
    void layoutAugmentationDots();
    qreal spaceBetweenNoteheadAndDot() const;
    qreal spaceBetweenAugmentationDots() const;
    qreal augmentationPositionAboveLine() const;
    GlyphItem *m_notehead;
    QVector<GlyphItem*> m_augmentationDots;
    bool m_onLine;
};

#endif // MELODYNOTEGLYPHITEM_H
