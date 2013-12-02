/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QGraphicsLinearLayout>
#include "graphicitems/textwidget.h"
#include "graphicitems/textrowwidget.h"
#include "../iteminteraction.h"
#include "scoregraphicsitem.h"

ScoreGraphicsItem::ScoreGraphicsItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_rowLayout(0)
{
    m_rowLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    m_rowLayout->setContentsMargins(0, 0, 0, 0);

    appendRow();

    createConnections();
}

void ScoreGraphicsItem::appendRow()
{
    TextRowWidget *newRow = new TextRowWidget();
    m_textRows.append(newRow);
    m_rowLayout->addItem(newRow);

    connect(newRow, SIGNAL(textChanged(TextRowWidget::RowAlignment,QString)),
            this, SLOT(textRowItemChanged(TextRowWidget::RowAlignment,QString)));
}

void ScoreGraphicsItem::createConnections()
{
    connect(this, &InteractingGraphicsItem::itemInteractionChanged,
            this, &ScoreGraphicsItem::itemInteractionChanged);
}

void ScoreGraphicsItem::itemInteractionChanged()
{
    // Connect to new item interaction object
    ItemInteraction *interaction = itemInteraction();
    if (interaction == 0) return;

    connect(this, &ScoreGraphicsItem::itemTextChanged,
            interaction, &ItemInteraction::dataChanged);
}

void ScoreGraphicsItem::textRowItemChanged(TextRowWidget::RowAlignment position, const QString &newText)
{
    QObject *senderRow = sender();
    TextRowWidget *rowWidget = qobject_cast<TextRowWidget*>(senderRow);
    if (!rowWidget) return;

    int rowIndex = m_textRows.indexOf(rowWidget);
    if (rowIndex == -1) return;

    TextItemPosition itemPosition;
    itemPosition.rowIndex = rowIndex;
    itemPosition.rowPosition = position;

    if (!m_itemPositions.values().contains(itemPosition))
        return;

    LP::ScoreDataRole itemType = m_itemPositions.key(itemPosition);
    emit itemTextChanged(newText, itemType);
}

void ScoreGraphicsItem::addRowsUntilRowIndex(int index)
{
    if (m_rowLayout->count() >= index + 1)
        return;

    while (m_rowLayout->count() < index + 1) {
        appendRow();
    }
}

void ScoreGraphicsItem::setItemPosition(LP::ScoreDataRole itemType, int row, TextRowWidget::RowAlignment position)
{
    if (row < 0)
        return;

    TextItemPosition itemPosition;
    if (hasItemPositionForDataRole(itemType))
        itemPosition = m_itemPositions.value(itemType);

    addRowsUntilRowIndex(row);
    itemPosition.rowIndex = row;
    itemPosition.rowPosition = position;

    m_itemPositions.insert(itemType, itemPosition);
}

int ScoreGraphicsItem::rowOfDataRole(LP::ScoreDataRole dataRole)
{
    if (!m_itemPositions.contains(dataRole))
        return -1;

    TextItemPosition itemPosition = m_itemPositions.value(dataRole);
    return itemPosition.rowIndex;
}

TextRowWidget::RowAlignment ScoreGraphicsItem::rowAlignmentOfDataRole(LP::ScoreDataRole dataRole)
{
    if (!m_itemPositions.contains(dataRole))
        return TextRowWidget::NoAlignment;

    TextItemPosition itemPosition = m_itemPositions.value(dataRole);
    return itemPosition.rowPosition;
}

bool ScoreGraphicsItem::hasItemPositionForDataRole(LP::ScoreDataRole itemType)
{
    if (m_itemPositions.contains(itemType))
        return true;
    return false;
}

void ScoreGraphicsItem::setItemText(LP::ScoreDataRole itemType, const QString &text)
{
    if (!hasItemPositionForDataRole(itemType)) {
        qWarning("No item position set for data role");
        return;
    }

    TextItemPosition position = m_itemPositions.value(itemType);
    if (m_textRows.count() - 1 > position.rowIndex)
        addRowsUntilRowIndex(position.rowIndex);

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    if (row->text(position.rowPosition) != text)
        row->setText(position.rowPosition, text);
}

QString ScoreGraphicsItem::itemText(LP::ScoreDataRole itemType)
{
    if (!hasItemPositionForDataRole(itemType))
        return QString();

    TextItemPosition position = m_itemPositions.value(itemType);
    if (!m_textRows.count() > position.rowIndex)
        return QString();

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    return row->text(position.rowPosition);
}

void ScoreGraphicsItem::setItemFont(LP::ScoreDataRole itemType, const QFont &font)
{
    if (!hasItemPositionForDataRole(itemType))
        return;

    TextItemPosition position = m_itemPositions.value(itemType);
    if (m_textRows.count() - 1 > position.rowIndex)
        addRowsUntilRowIndex(position.rowIndex);

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    row->setFont(position.rowPosition, font);
}

void ScoreGraphicsItem::setItemColor(LP::ScoreDataRole itemType, const QColor &color)
{
    if (!hasItemPositionForDataRole(itemType))
        return;

    TextItemPosition position = m_itemPositions.value(itemType);
    if (m_textRows.count() - 1 > position.rowIndex)
        addRowsUntilRowIndex(position.rowIndex);

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    row->setColor(position.rowPosition, color);
}

bool ScoreGraphicsItem::TextItemPosition::operator ==(const ScoreGraphicsItem::TextItemPosition &other) const
{
    if (rowIndex == other.rowIndex &&
            rowPosition == other.rowPosition)
        return true;
    return false;
}
