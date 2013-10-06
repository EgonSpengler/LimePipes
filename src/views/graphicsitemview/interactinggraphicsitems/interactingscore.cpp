/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "graphicalscoreitem.h"
#include "interactingscore.h"

InteractingScore::InteractingScore(QObject *parent)
    : AbstractScorePropertiesItem(parent),
      m_headerItem(0),
      m_footerItem(0)
{
    m_headerItem = new GraphicalScoreItem();
    m_footerItem = new GraphicalScoreItem();
}

InteractingScore::~InteractingScore()
{
    delete m_headerItem;
    delete m_footerItem;
}


void InteractingScore::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void InteractingScore::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void InteractingScore::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void InteractingScore::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void InteractingScore::setNewTitle(const QString &title)
{
    m_headerItem->setTitle(title);
    m_footerItem->setTitle(title);
}

void InteractingScore::setNewComposer(const QString &composer)
{
}

void InteractingScore::setNewArranger(const QString &arranger)
{
}

void InteractingScore::setNewYear(const QString &year)
{
}

void InteractingScore::setNewCopyright(const QString &copyright)
{
}

void InteractingScore::setNewTimeSignature(const TimeSignature &timeSig)
{
}
