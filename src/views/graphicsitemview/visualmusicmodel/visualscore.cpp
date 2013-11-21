/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "interactinggraphicsitems/scoregraphicsitem.h"
#include "iteminteractions/scoreinteraction.h"
#include "visualscore.h"

VisualScore::VisualScore(QObject *parent)
    : VisualItem(parent),
      m_headerItem(0),
      m_footerItem(0)
{
    m_headerItem = new ScoreGraphicsItem();
    m_headerItem->setItemInteraction(new ScoreInteraction);
    m_headerItem->setItemPosition(LP::ScoreType, 0, TextRowWidget::Left);
    m_headerItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    QFont font;
    font.setPointSize(16);
    m_headerItem->setItemFont(LP::ScoreTitle, font);
    m_headerItem->setItemPosition(LP::ScoreComposer, 0, TextRowWidget::Right);
    m_headerItem->setItemPosition(LP::ScoreArranger, 1, TextRowWidget::Right);

    m_footerItem = new ScoreGraphicsItem();
    m_footerItem->setItemPosition(LP::ScoreYear, 0, TextRowWidget::Left);
    m_footerItem->setItemPosition(LP::ScoreCopyright, 0, TextRowWidget::Right);
    m_footerItem->setItemInteraction(new ScoreInteraction);

    createConnections();
}

void VisualScore::createConnections()
{
    connect(m_headerItem, SIGNAL(itemTextChanged(LP::ScoreDataRole,QString)),
            this, SLOT(scoreGraphicsTextChanged(LP::ScoreDataRole,QString)));
    connect(m_footerItem, SIGNAL(itemTextChanged(LP::ScoreDataRole,QString)),
            this, SLOT(scoreGraphicsTextChanged(LP::ScoreDataRole,QString)));
}

VisualItem::ItemType VisualScore::itemType() const
{
    return VisualItem::VisualScoreItem;
}

void VisualScore::setDataFromIndex(const QPersistentModelIndex &index)
{
}

ScoreGraphicsItem *VisualScore::headerItem() const
{
    return m_headerItem;
}

ScoreGraphicsItem *VisualScore::footerItem() const
{
    return m_footerItem;
}

void VisualScore::scoreGraphicsTextChanged(LP::ScoreDataRole data, const QString &text)
{
    emit dataChanged(text, data);
}

VisualItem::GraphicalType VisualScore::graphicalType() const
{
    return VisualItem::GraphicalRowType;
}

QList<InteractingGraphicsItem *> VisualScore::rowGraphics() const
{
    QList<InteractingGraphicsItem *> items;
    return items;
}
