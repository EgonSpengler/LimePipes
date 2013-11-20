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
    : VisualItem(parent)
{
    createConnections();
}

void VisualScore::createConnections()
{
}

VisualItem::ItemType VisualScore::itemType() const
{
    return VisualItem::VisualScoreItem;
}

void VisualScore::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void VisualScore::titleChanged(const QString &title)
{
    emit dataChanged(title, LP::ScoreTitle);
}
