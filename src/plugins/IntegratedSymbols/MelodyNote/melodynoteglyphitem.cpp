/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include "melodynoteglyphitem.h"

static const QString WholeNoteHead("noteheadWhole");
static const QString HalfNoteHead("noteheadHalf");
static const QString BlackNoteHead("noteheadBlack");
static const QString AugmentationDot("augmentationDot");

static int MaxDots(4);

MelodyNoteGlyphItem::MelodyNoteGlyphItem()
    : GlyphItem(),
      m_onLine(false)
{
    m_notehead = new GlyphItem(this);
}

void MelodyNoteGlyphItem::setLength(Length::Value length)
{
    m_notehead->setGlyphName(noteheadForLength(length));
}

void MelodyNoteGlyphItem::setNoteIsOnLine(bool onLine)
{
    if (m_onLine == onLine)
        return;

    m_onLine = onLine;
    layoutAugmentationDots();
}

void MelodyNoteGlyphItem::setDots(int dots)
{
    if (dots < 0)
        dots = 0;
    if (dots > MaxDots)
        dots = MaxDots;

    if (dots == m_augmentationDots.count())
        return;

    setAugmentationDots(dots);
    prepareGeometryChange();
}

void MelodyNoteGlyphItem::setAugmentationDots(int dotCount)
{
    setDotGlyphCount(dotCount);
    layoutAugmentationDots();
}

/*!
 * \brief MelodyNoteGlyphItem::setDotGlyphCount
 *        Set the augmentation dot glyphs. If a GlyphItem is added, it will be set
 *        hidden.
 * \param dotCount
 */
void MelodyNoteGlyphItem::setDotGlyphCount(int dotCount)
{
    if (m_augmentationDots.count() == dotCount)
        return;

    if (m_augmentationDots.count() < dotCount) {
        while (m_augmentationDots.count() < dotCount) {
            GlyphItem *newDot = new GlyphItem(AugmentationDot, this);
            newDot->setSmufl(smufl());
            newDot->setVisible(false);
            m_augmentationDots.append(newDot);
        }
    }

    if (m_augmentationDots.count() > dotCount) {
        while (m_augmentationDots.count() > dotCount) {
            GlyphItem *augmentationDot = m_augmentationDots.takeLast();
            if (augmentationDot != 0) {
                augmentationDot->setParentItem(0);
                delete augmentationDot;
            }
        }
    }
}

void MelodyNoteGlyphItem::layoutAugmentationDots()
{
    qreal leftEdge = mapFromItem(m_notehead, m_notehead->boundingRect().topRight()).x();
    leftEdge += spaceBetweenNoteheadAndDot();

    for (int i = 0; i < m_augmentationDots.count(); ++i) {
        GlyphItem *dot = m_augmentationDots.at(i);
        qreal dotOffset = dot->boundingRect().width() + spaceBetweenAugmentationDots();
        dot->setX(leftEdge + i * dotOffset);
        if (m_onLine) {
            dot->setY(augmentationPositionAboveLine());
        } else {
            dot->setY(0);
        }
        dot->setVisible(true);
    }
}

qreal MelodyNoteGlyphItem::spaceBetweenNoteheadAndDot() const
{
    return 5;
}

qreal MelodyNoteGlyphItem::spaceBetweenAugmentationDots() const
{
    return 3;
}

qreal MelodyNoteGlyphItem::augmentationPositionAboveLine() const
{
    return -5;
}

QString MelodyNoteGlyphItem::noteheadForLength(Length::Value length)
{
    switch (length) {
    case Length::_1:
        return WholeNoteHead; break;
    case Length::_2:
        return HalfNoteHead; break;
    default:
        return BlackNoteHead; break;
    }
}

void MelodyNoteGlyphItem::smuflHasChanged(const SMuFLPtr &smufl)
{
    m_notehead->setSmufl(smufl);
    for (int i = 0; i < m_augmentationDots.count(); ++i) {
        m_augmentationDots.at(i)->setSmufl(smufl);
    }
}
