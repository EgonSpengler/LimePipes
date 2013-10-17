/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QGraphicsLinearLayout>
#include "graphicitems/textwidget.h"
#include "graphicalscoreitem.h"

GraphicalScoreItem::GraphicalScoreItem(QGraphicsItem *parent)
    : InteractingGraphicsItem(parent),
      m_titleItem(0),
      m_rowLayout(0)
{
    m_rowLayout = new QGraphicsLinearLayout(Qt::Vertical, this);
    m_rowLayout->setContentsMargins(0, 0, 0, 0);
}

void GraphicalScoreItem::setTitle(const QString &title)
{
    if (!title.isEmpty()) {
        if (m_titleItem == 0) {
            m_titleItem = new TextWidget(this);
            m_rowLayout->addItem(m_titleItem);
            m_titleItem->setText(title);
            connect(m_titleItem, SIGNAL(textChanged(QString)),
                    this, SIGNAL(titleChanged(QString)));
        }
        else
            m_titleItem->setText(title);
    }
    else {
        if (m_titleItem != 0) {
            delete m_titleItem;
            m_titleItem = 0;
        }
    }
}

QString GraphicalScoreItem::title() const
{
    if (!m_titleItem)
        return QString();

    return m_titleItem->text();
}
