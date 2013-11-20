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
    : AbstractVisualItem(parent)
{
    createConnections();
}

void VisualScore::createConnections()
{
}

AbstractVisualItem::Type VisualScore::type() const
{
    return AbstractVisualItem::VisualScoreItem;
}

void VisualScore::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualScore::titleChanged(const QString &title)
{
    emit dataChanged(title, LP::ScoreTitle);
}
