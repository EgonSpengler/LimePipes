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
#include "graphicalscoreitem.h"

GraphicalScoreItem::GraphicalScoreItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_rowLayout(0)
{
    m_rowLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    m_rowLayout->setContentsMargins(0, 0, 0, 0);

    appendRow();
}

void GraphicalScoreItem::appendRow()
{
    TextRowWidget *newRow = new TextRowWidget();
    m_textRows.append(newRow);
    m_rowLayout->addItem(newRow);
}

void GraphicalScoreItem::setTitle(const QString &title)
{
    if (!m_itemPostions.contains(Title))
        return;

    ItemPosition position = m_itemPostions.value(Title);
    if (m_textRows.count() - 1 > position.rowIndex)
        addRowsUntilRowIndex(position.rowIndex);

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    row->setText(position.rowPosition, title);
}

void GraphicalScoreItem::addRowsUntilRowIndex(int index)
{
    if (m_rowLayout->count() >= index + 1)
        return;

    while (m_rowLayout->count() < index + 1) {
        appendRow();
    }
}

QString GraphicalScoreItem::title() const
{
    if (!m_itemPostions.contains(Title))
        return QString();

    ItemPosition position = m_itemPostions.value(Title);
    if (!m_textRows.count() > position.rowIndex)
        return QString();

    TextRowWidget *row = m_textRows.at(position.rowIndex);
    return row->text(position.rowPosition);
}

