/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "visualscore.h"

VisualScore::VisualScore(QObject *parent)
    : AbstractScorePropertiesItem(parent),
      m_graphicalScore(0)
{
}

AbstractVisualItem::Type VisualScore::type() const
{
    return AbstractVisualItem::VisualScoreItem;
}

void VisualScore::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualScore::setNewTitle(const QString &title)
{
}

void VisualScore::setNewComposer(const QString &composer)
{
}

void VisualScore::setNewArranger(const QString &arranger)
{
}

void VisualScore::setNewYear(const QString &year)
{
}

void VisualScore::setNewCopyright(const QString &copyright)
{
}

void VisualScore::setNewTimeSignature(const TimeSignature &timeSig)
{
}

GraphicalScoreInterface *VisualScore::graphicalScore() const
{
    return m_graphicalScore;
}

void VisualScore::setGraphicalScore(GraphicalScoreInterface *graphicalScore)
{
    m_graphicalScore = graphicalScore;
}
