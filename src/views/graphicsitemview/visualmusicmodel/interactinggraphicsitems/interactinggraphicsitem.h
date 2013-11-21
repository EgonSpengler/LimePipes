/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INTERACTINGGRAPHICSITEM_H
#define INTERACTINGGRAPHICSITEM_H

#include <QGraphicsWidget>

class ItemInteraction;

class InteractingGraphicsItem : public QGraphicsWidget
{
    friend class InteractingGraphicsItemTest;

public:
    explicit InteractingGraphicsItem(QGraphicsItem *parent = 0);
    virtual ~InteractingGraphicsItem() {}

    ItemInteraction *itemInteraction() const;

    /*!
     * \brief setItemInteraction
     * \param itemInteraction The interaction object for this item.
     *        This item takes ownership of the interaction object.
     */
    void setItemInteraction(ItemInteraction *itemInteraction);

    virtual void insertChildItem(int index, InteractingGraphicsItem *childItem)
    {
        Q_UNUSED(index);
        Q_UNUSED(childItem);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    ItemInteraction *m_itemInteraction;
};

#endif // INTERACTINGGRAPHICSITEM_H
