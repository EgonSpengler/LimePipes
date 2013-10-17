/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICALSCOREITEM_H
#define GRAPHICALSCOREITEM_H

#include "interactinggraphicsitem.h"
#include <graphicsitemview/scorepropertiesinterface.h>

class TextWidget;
class QGraphicsLinearLayout;

class GraphicalScoreItem : public InteractingGraphicsItem
{
    Q_OBJECT

    friend class GraphicalScoreItemTest;

public:
    explicit GraphicalScoreItem(QGraphicsItem *parent = 0);

    void setTitle(const QString& title);
    QString title() const;

signals:
    void titleChanged(const QString& title);

private:
    TextWidget *m_titleItem;
    QGraphicsLinearLayout *m_rowLayout;
};

#endif // GRAPHICALSCOREITEM_H
