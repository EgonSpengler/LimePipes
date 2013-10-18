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
    QString title = index.data(LP::scoreTitle).toString();
    m_scorePropertiesItem->setTitle(title);

    QString composer = index.data(LP::scoreComposer).toString();
    m_scorePropertiesItem->setComposer(composer);

    QString arranger = index.data(LP::scoreArranger).toString();
    m_scorePropertiesItem->setArranger(arranger);

    QString year = index.data(LP::scoreYear).toString();
    m_scorePropertiesItem->setYear(year);

    QString copyright = index.data(LP::scoreCopyright).toString();
    m_scorePropertiesItem->setCopyright(copyright);

    QVariant timeSigVariant = index.data(LP::scoreTimeSignature);
    m_scorePropertiesItem->setTimeSignature(timeSigVariant.value<TimeSignature>());
}

void VisualScore::titleChanged(const QString &title)
{
    emit dataChanged(title, LP::scoreTitle);
}

ScorePropertiesItem *VisualScore::scorePropertiesItem() const
{
    return m_scorePropertiesItem;
}
