/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "graphicalscoreitem.h"
#include "dialogs/scorepropertiesdialog.h"
#include "interactingscore.h"

InteractingScore::InteractingScore(QObject *parent)
    : QObject(parent),
      m_headerItem(0),
      m_footerItem(0)
{
    m_scorePropertiesItem = new ScorePropertiesItem(this);
    m_scorePropertiesDialog = new ScorePropertiesDialog();

    m_headerItem = new GraphicalScoreItem();
    m_headerItem->setInteractingItem(this);
    m_headerItem->setItemPosition(GraphicalScoreItem::Title, 0, TextRowWidget::Center);
    m_headerItem->setItemPosition(GraphicalScoreItem::Composer, 0, TextRowWidget::Right);
    m_footerItem = new GraphicalScoreItem();
    m_footerItem->setInteractingItem(this);

    createConnections();
}

InteractingScore::~InteractingScore()
{
    delete m_scorePropertiesDialog;
}

void InteractingScore::createConnections()
{
    connect(m_headerItem, SIGNAL(titleChanged(QString)),
            m_scorePropertiesItem, SLOT(setTitle(QString)));
    connect(m_footerItem, SIGNAL(titleChanged(QString)),
            m_scorePropertiesItem, SLOT(setTitle(QString)));

    connect(m_scorePropertiesItem, SIGNAL(titleChanged(QString)),
            this, SLOT(setTitle(QString)));

    connect(m_scorePropertiesItem, SIGNAL(titleChanged(QString)),
            m_scorePropertiesDialog, SLOT(setTitle(QString)));
    connect(m_scorePropertiesDialog, SIGNAL(titleChanged(QString)),
            this, SLOT(setTitle(QString)));

    connect(m_scorePropertiesDialog, SIGNAL(titleFontChanged(QFont)),
            this, SLOT(titleFontChanged(QFont)));
    connect(m_scorePropertiesDialog, SIGNAL(titleColorChanged(QColor)),
            this, SLOT(titleColorChanged(QColor)));
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

void InteractingScore::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    m_scorePropertiesDialog->show();
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

void InteractingScore::titleFontChanged(const QFont &font)
{
    m_headerItem->setItemFont(GraphicalScoreItem::Title, font);
    m_footerItem->setItemFont(GraphicalScoreItem::Title, font);
}

void InteractingScore::titleColorChanged(const QColor &color)
{
    m_headerItem->setItemColor(GraphicalScoreItem::Title, color);
    m_footerItem->setItemColor(GraphicalScoreItem::Title, color);
}

