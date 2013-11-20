/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include "scoregraphicsitem.h"
#include "dialogs/scorepropertiesdialog.h"
#include "scoreinteraction.h"

ScoreInteraction::ScoreInteraction(QObject *parent)
    : ItemInteraction(parent),
      m_headerItem(0),
      m_footerItem(0)
{
    m_scorePropertiesDialog = new ScorePropertiesDialog();

    m_headerItem = new ScoreGraphicsItem();
    m_headerItem->setItemInteraction(this);
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
    m_footerItem->setItemInteraction(this);

    createConnections();
}

ScoreInteraction::~ScoreInteraction()
{
    delete m_scorePropertiesDialog;
}

void ScoreInteraction::createConnections()
{
    connect(m_scorePropertiesItem, SIGNAL(titleChanged(QString)),
            this, SLOT(setTitle(QString)));

    connect(m_headerItem, SIGNAL(itemTextChanged(LP::ScoreDataRole,QString)),
            this, SLOT(propertyTextChanged(LP::ScoreDataRole,QString)));
    connect(m_footerItem, SIGNAL(itemTextChanged(LP::ScoreDataRole,QString)),
            this, SLOT(propertyTextChanged(LP::ScoreDataRole,QString)));

    connect(m_scorePropertiesDialog, SIGNAL(propertyTextChanged(LP::ScoreDataRole,QString)),
            this, SLOT(propertyTextChanged(LP::ScoreDataRole,QString)));
    connect(m_scorePropertiesDialog, SIGNAL(propertyFontChanged(LP::ScoreDataRole,QFont)),
            this, SLOT(propertyFontChanged(LP::ScoreDataRole,QFont)));
    connect(m_scorePropertiesDialog, SIGNAL(propertyColorChanged(LP::ScoreDataRole,QColor)),
            this, SLOT(propertyColorChanged(LP::ScoreDataRole,QColor)));
}

QGraphicsWidget *ScoreInteraction::headerItem() const
{
    return static_cast<QGraphicsWidget*>(m_headerItem);
}

QGraphicsWidget *ScoreInteraction::footerItem() const
{
    return static_cast<QGraphicsWidget*>(m_footerItem);
}

void ScoreInteraction::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ScoreInteraction::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ScoreInteraction::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ScoreInteraction::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ScoreInteraction::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    m_scorePropertiesDialog->show();
    Q_UNUSED(event);
}

ScorePropertiesItem *ScoreInteraction::scorePropertiesItem() const
{
    return m_scorePropertiesItem;
}

void ScoreInteraction::propertyTextChanged(LP::ScoreDataRole dataRole, const QString &text)
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

void ScoreInteraction::propertyFontChanged(LP::ScoreDataRole dataRole, const QFont &font)
{
    m_headerItem->setItemFont(LP::ScoreTitle, font);
    m_footerItem->setItemFont(LP::ScoreTitle, font);
}

void ScoreInteraction::propertyColorChanged(LP::ScoreDataRole dataRole, const QColor &color)
{
    m_headerItem->setItemColor(LP::ScoreTitle, color);
    m_footerItem->setItemColor(LP::ScoreTitle, color);
}

void ScoreInteraction::setTitle(const QString &title)
{
    propertyTextChanged(LP::ScoreTitle, title);
}

void ScoreInteraction::setType(const QString &type)
{
}

void ScoreInteraction::setComposer(const QString &composer)
{
}

void ScoreInteraction::setArranger(const QString &arranger)
{
}

void ScoreInteraction::setYear(const QString &year)
{
}

void ScoreInteraction::setCopyright(const QString &copyright)
{
}
