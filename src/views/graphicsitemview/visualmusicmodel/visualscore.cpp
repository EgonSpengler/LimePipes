/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <itemdatatypes.h>
#include "visualscore.h"

VisualScore::VisualScore(QObject *parent)
    : ScorePropertiesItem(parent)
{
}

AbstractVisualItem::Type VisualScore::type() const
{
    return AbstractVisualItem::VisualScoreItem;
}

void VisualScore::setDataFromIndex(const QPersistentModelIndex &index)
{
    QString title = index.data(LP::scoreTitle).toString();
    setTitle(title);

    QString composer = index.data(LP::scoreComposer).toString();
    setComposer(composer);

    QString arranger = index.data(LP::scoreArranger).toString();
    setArranger(arranger);

    QString year = index.data(LP::scoreYear).toString();
    setYear(year);

    QString copyright = index.data(LP::scoreCopyright).toString();
    setCopyright(copyright);

    QVariant timeSigVariant = index.data(LP::scoreTimeSignature);
    setTimeSignature(timeSigVariant.value<TimeSignature>());
}

void VisualScore::setTitle(const QString &title)
{
    ScorePropertiesItem::setTitle(title);

    emit dataChanged(title, LP::scoreTitle);
}
