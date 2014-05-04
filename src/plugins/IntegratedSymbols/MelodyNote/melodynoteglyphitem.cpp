/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QPen>
#include <QDebug>
#include "../integratedsymbolsdefines.h"
#include "melodynoteglyphitem.h"

static const QString WholeNoteHead("noteheadWhole");
static const QString HalfNoteHead("noteheadHalf");
static const QString BlackNoteHead("noteheadBlack");
static const QString AugmentationDot("augmentationDot");

MelodyNoteGlyphItem::MelodyNoteGlyphItem()
    : GlyphItem(),
      m_ledgerPosition(LedgerLinePosition::Below),
      m_onLine(false)
{
    setFlag(QGraphicsItem::ItemIsFocusable, true);
    m_notehead = new GlyphItem(this);
    m_notehead->setFocusProxy(this);
}

void MelodyNoteGlyphItem::setLength(Length::Value length)
{
    m_notehead->setGlyphName(noteheadForLength(length));
    layoutNoteHead();
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
    if (dots > MelodyNoteMaxDots)
        dots = MelodyNoteMaxDots;

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
            newDot->setMusicFont(musicFont());
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

void MelodyNoteGlyphItem::setLedgerLines(int count, bool aboveNotehead)
{
    if (count < 0 ||
            m_ledgerLines.count() == count)
        return;

    if (aboveNotehead) {
        m_ledgerPosition = LedgerLinePosition::Above;
    } else {
        m_ledgerPosition = LedgerLinePosition::Below;
    }

    setLedgerLinesItems(count);
    layoutLedgerLineItems();
    layoutNoteHead();
    layoutAugmentationDots();
    prepareGeometryChange();
}

QPen MelodyNoteGlyphItem::ledgerLinePen() const
{
    QPen linePen;
    qreal ledgerLineThickness = musicFont()->engravings().legerLineThickness * musicFont()->staffSpace();
    linePen.setWidthF(ledgerLineThickness);

    return linePen;
}

void MelodyNoteGlyphItem::setLedgerLinesItems(int count)
{
    if (m_ledgerLines.count() == count)
        return;

    if (m_ledgerLines.count() < count) {
        QPen linePen = ledgerLinePen();

        while (m_ledgerLines.count() < count) {
            QGraphicsLineItem *newLedgerLine = new QGraphicsLineItem(this);
            newLedgerLine->setPen(linePen);
            newLedgerLine->setVisible(false);
            m_ledgerLines.append(newLedgerLine);
        }
    }

    if (m_ledgerLines.count() > count) {
        while (m_ledgerLines.count() > count) {
            QGraphicsLineItem *ledgerLine = m_ledgerLines.takeLast();
            if (ledgerLine != 0) {
                ledgerLine->setParentItem(0);
                delete ledgerLine;
            }
        }
    }
}

void MelodyNoteGlyphItem::layoutNoteHead()
{
    if (hasLedgerLines()) {
        m_notehead->setX(ledgerLineExtensionWidth());
    } else {
        m_notehead->setX(0);
    }
}

void MelodyNoteGlyphItem::layoutLedgerLineItems()
{
    if (!m_ledgerLines.count())
        return;

    qreal halfStaffSpace = musicFont()->halfStaffSpace();
    qreal noteHeadWidth = m_notehead->boundingRect().width();
    qreal ledgerLineWidth = noteHeadWidth + 2 * ledgerLineExtensionWidth();

    for (int i = 0; i < m_ledgerLines.count(); ++i) {
        qreal yPos = i * halfStaffSpace;
        if (m_ledgerPosition == LedgerLinePosition::Above) {
            yPos *= -1;
        }

        QGraphicsLineItem *ledgerLineItem = m_ledgerLines.at(i);
        ledgerLineItem->setLine(0, yPos, ledgerLineWidth, yPos);
        ledgerLineItem->setVisible(true);
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
    return musicFont()->font().pixelSize() / 14;
}

qreal MelodyNoteGlyphItem::spaceBetweenAugmentationDots() const
{
    return musicFont()->font().pixelSize() / 24;
}

qreal MelodyNoteGlyphItem::augmentationPositionAboveLine() const
{
    return -musicFont()->halfStaffSpace();
}

bool MelodyNoteGlyphItem::hasLedgerLines() const
{
    return m_ledgerLines.count();
}

/*!
 * \brief MelodyNoteGlyphItem::ledgerLineExtensionWidth
 *        The width, which a leger line extends the note head on a side.
 * \return  The width
 */
qreal MelodyNoteGlyphItem::ledgerLineExtensionWidth() const
{
    qreal ledgerLineExtension = musicFont()->engravings().legerLineExtension;
    return ledgerLineExtension * musicFont()->staffSpace() / 2;
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

void MelodyNoteGlyphItem::musicFontHasChanged(const MusicFontPtr &musicFont)
{
    m_notehead->setMusicFont(musicFont);
    for (int i = 0; i < m_augmentationDots.count(); ++i) {
        m_augmentationDots.at(i)->setMusicFont(musicFont);
    }

    QPen ledgerPen = ledgerLinePen();
    for (int i = 0; i < m_ledgerLines.count(); ++i) {
        m_ledgerLines.at(i)->setPen(ledgerPen);
    }
}

void MelodyNoteGlyphItem::colorRoleHasChanged(QPalette::ColorRole colorRole)
{
    m_notehead->setColorRole(colorRole);
}
