/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <itemdatatypes.h>
#include "../scorepropertiesitem.h"
#include "visualscore.h"

VisualScore::VisualScore(QObject *parent)
    : AbstractVisualItem(parent),
      m_scorePropertiesItem(0)
{
    m_scorePropertiesItem = new ScorePropertiesItem(this);

    createConnections();
}

void VisualScore::createConnections()
{
    connect(m_scorePropertiesItem, SIGNAL(titleChanged(QString)),
            this, SLOT(titleChanged(QString)));
}

AbstractVisualItem::Type VisualScore::type() const
{
    return AbstractVisualItem::VisualScoreItem;
}

void VisualScore::setDataFromIndex(const QPersistentModelIndex &index)
{
    QString title = index.data(LP::ScoreTitle).toString();
    m_scorePropertiesItem->setTitle(title);

    QString type = index.data(LP::ScoreType).toString();
    m_scorePropertiesItem->setType(type);

    QString composer = index.data(LP::ScoreComposer).toString();
    m_scorePropertiesItem->setComposer(composer);

    QString arranger = index.data(LP::ScoreArranger).toString();
    m_scorePropertiesItem->setArranger(arranger);

    QString year = index.data(LP::ScoreYear).toString();
    m_scorePropertiesItem->setYear(year);

    QString copyright = index.data(LP::ScoreCopyright).toString();
    m_scorePropertiesItem->setCopyright(copyright);
}

void VisualScore::titleChanged(const QString &title)
{
    emit dataChanged(title, LP::ScoreTitle);
}

ScorePropertiesItem *VisualScore::scorePropertiesItem() const
{
    return m_scorePropertiesItem;
}
