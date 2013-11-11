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
    m_headerItem->setItemPosition(LP::ScoreTitle, 0, TextRowWidget::Center);
    m_headerItem->setItemPosition(LP::ScoreComposer, 0, TextRowWidget::Right);
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
    connect(m_scorePropertiesItem, SIGNAL(titleChanged(QString)),
            this, SLOT(setTitle(QString)));

    connect(m_headerItem, SIGNAL(itemTextChanged(LP::ScoreDataRole,QString)),
            this, SLOT(propertyTextChanged(LP::ScoreDataRole,QString)));
    connect(m_footerItem, SIGNAL(itemTextChanged(LP::ScoreDataRole,QString)),
            this, SLOT(propertyTextChanged(LP::ScoreDataRole,QString)));
    connect(m_scorePropertiesDialog, SIGNAL(propertyTextChanged(LP::ScoreDataRole,QString)),
            this, SLOT(propertyTextChanged(LP::ScoreDataRole,QString)));

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

void InteractingScore::propertyTextChanged(LP::ScoreDataRole dataRole, const QString &text)
{
    m_headerItem->setItemText(dataRole, text);
    m_footerItem->setItemText(dataRole, text);

    m_scorePropertiesDialog->setPropertyText(dataRole, text);

    // ScorePropertiesItem
    switch (dataRole) {
    case LP::ScoreType:
        m_scorePropertiesItem->setType(text);
        break;
    case LP::ScoreTitle:
        m_scorePropertiesItem->setTitle(text);
        break;
    case LP::ScoreComposer:
        m_scorePropertiesItem->setComposer(text);
        break;
    case LP::ScoreArranger:
        m_scorePropertiesItem->setArranger(text);
        break;
    case LP::ScoreYear:
        m_scorePropertiesItem->setYear(text);
        break;
    case LP::ScoreCopyright:
        m_scorePropertiesItem->setCopyright(text);
        break;
    }
}

void InteractingScore::propertyFontChanged(LP::ScoreDataRole dataRole, const QFont &font)
{
    m_headerItem->setItemFont(LP::ScoreTitle, font);
    m_footerItem->setItemFont(LP::ScoreTitle, font);
}

void InteractingScore::propertyColorChanged(LP::ScoreDataRole dataRole, const QColor &color)
{
    m_headerItem->setItemColor(LP::ScoreTitle, color);
    m_footerItem->setItemColor(LP::ScoreTitle, color);
}

void InteractingScore::setTitle(const QString &title)
{
    propertyTextChanged(LP::ScoreTitle, title);
}

void InteractingScore::setType(const QString &type)
{
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
