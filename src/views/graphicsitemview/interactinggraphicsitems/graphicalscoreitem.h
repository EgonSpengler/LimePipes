/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICALSCOREITEM_H
#define GRAPHICALSCOREITEM_H

#include <QGraphicsTextItem>
#include "interactinggraphicsitem.h"

class GraphicalScoreItem : public InteractingGraphicsItem
{
    friend class GraphicalScoreItemTest;

public:
    explicit GraphicalScoreItem();

    void setTitle(const QString& title);
    QString title() const;

private:
    QGraphicsTextItem *m_titleItem;
};

#endif // GRAPHICALSCOREITEM_H
