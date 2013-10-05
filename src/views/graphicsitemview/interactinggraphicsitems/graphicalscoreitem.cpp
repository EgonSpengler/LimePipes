/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "graphicalscoreitem.h"

GraphicalScoreItem::GraphicalScoreItem(QObject *parent)
    : AbstractScorePropertiesHolder(parent),
      m_titleItem(0)
{
}

void GraphicalScoreItem::setTitle(const QString &title)
{
    if (!title.isEmpty()) {
        if (m_titleItem == 0)
            m_titleItem = new QGraphicsTextItem(title, this);
        else
            m_titleItem->setHtml(title);
    }
    else {
        if (m_titleItem != 0) {
            delete m_titleItem;
            m_titleItem = 0;
        }
    }
}

QString GraphicalScoreItem::title() const
{
    if (!m_titleItem)
        return QString();

    return m_titleItem->toPlainText();
}


void GraphicalScoreItem::setNewTitle(const QString &title)
{
}

void GraphicalScoreItem::setNewComposer(const QString &composer)
{
}

void GraphicalScoreItem::setNewArranger(const QString &arranger)
{
}

void GraphicalScoreItem::setNewYear(const QString &year)
{
}

void GraphicalScoreItem::setNewCopyright(const QString &copyright)
{
}

void GraphicalScoreItem::setNewTimeSignature(const TimeSignature &timeSig)
{
}
