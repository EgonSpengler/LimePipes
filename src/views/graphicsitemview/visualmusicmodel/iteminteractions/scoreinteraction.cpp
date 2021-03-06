/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QVariant>
#include "dialogs/scorepropertiesdialog.h"
#include "scoreinteraction.h"

ScoreInteraction::ScoreInteraction(QObject *parent)
    : ItemInteraction(parent)
{
    m_scorePropertiesDialog = new ScorePropertiesDialog();

    createConnections();
}

ScoreInteraction::~ScoreInteraction()
{
    delete m_scorePropertiesDialog;
}

void ScoreInteraction::createConnections()
{
    connect(m_scorePropertiesDialog, &ScorePropertiesDialog::propertyTextChanged,
            this, &ScoreInteraction::propertyTextChanged);
}

void ScoreInteraction::mousePressEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ScoreInteraction::mouseMoveEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ScoreInteraction::mouseReleaseEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ScoreInteraction::mouseDoubleClickEvent(const QGraphicsItem *item, QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void ScoreInteraction::contextMenuEvent(const QGraphicsItem *item, QGraphicsSceneContextMenuEvent *event)
{
    m_scorePropertiesDialog->show();
    Q_UNUSED(event);
}

void ScoreInteraction::setData(const QVariant &value, int role)
{
    m_scorePropertiesDialog->setPropertyText(role, value.toString());
}

void ScoreInteraction::propertyTextChanged(LP::ScoreDataRole dataRole, const QString &text)
{
    int role = static_cast<int>(dataRole);
    emit dataChanged(text, role);
}
