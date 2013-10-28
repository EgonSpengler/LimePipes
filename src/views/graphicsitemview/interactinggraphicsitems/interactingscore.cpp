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
    : m_headerItem(0),
      m_footerItem(0)
{
    m_scorePropertiesItem = new ScorePropertiesItem(this);

    m_headerItem = new GraphicalScoreItem();
    m_headerItem->setInteractingItem(this);
    m_headerItem->setItemPosition(GraphicalScoreItem::Title, 0, TextRowWidget::Center);
    m_footerItem = new GraphicalScoreItem();
    m_footerItem->setInteractingItem(this);

    createConnections();
}

void InteractingScore::createConnections()
{
    connect(m_headerItem, SIGNAL(titleChanged(QString)),
            m_scorePropertiesItem, SLOT(setTitle(QString)));
    connect(m_footerItem, SIGNAL(titleChanged(QString)),
            m_scorePropertiesItem, SLOT(setTitle(QString)));

    connect(m_scorePropertiesItem, SIGNAL(titleChanged(QString)),
            this, SLOT(setTitle(QString)));
}

InteractingScore::~InteractingScore()
{
}

QGraphicsWidget *InteractingScore::headerItem() const
{
    return static_cast<QGraphicsWidget*>(m_headerItem);
}

QGraphicsWidget *InteractingScore::footerItem() const
{
    return static_cast<QGraphicsWidget*>(m_footerItem);
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

ScorePropertiesItem *InteractingScore::scorePropertiesItem() const
{
    return m_scorePropertiesItem;
}

void InteractingScore::setTitle(const QString &title)
{
    m_scorePropertiesItem->setTitle(title);

    m_headerItem->setTitle(title);
    m_footerItem->setTitle(title);
}

void InteractingScore::setComposer(const QString &composer)
{
}

void InteractingScore::setArranger(const QString &arranger)
{
}

void InteractingScore::setYear(const QString &year)
{
}

void InteractingScore::setCopyright(const QString &copyright)
{
}

void InteractingScore::setTimeSignature(const TimeSignature &timeSig)
{
}
