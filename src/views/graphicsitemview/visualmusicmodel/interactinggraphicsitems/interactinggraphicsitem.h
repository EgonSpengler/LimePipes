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
    Q_OBJECT

    friend class InteractingGraphicsItemTest;

public:
    explicit InteractingGraphicsItem(QGraphicsItem *parent = 0);
    virtual ~InteractingGraphicsItem() {}

    /*!
     * \brief setItemInteraction
     * \param itemInteraction The interaction object for this item.
     *        This item takes ownership of the interaction object.
     */
    void setItemInteraction(ItemInteraction *itemInteraction);
    ItemInteraction *itemInteraction() const;

    /*!
     * \brief insertChildItem Can be reimplemented by subclasses to insert child items into
     *          the layout.
     * \param index The position in the layout for the item
     * \param childItem The item to insert into the layout
     */
    virtual void insertChildItem(int index, InteractingGraphicsItem *childItem)
    {
        Q_UNUSED(index);
        Q_UNUSED(childItem);
    }

    /*!
     * \brief setData Can be reimplemented by subclasses to set the data in its own specific way.
     * \param value The new value
     * \param key The data role as int
     */
    virtual void setData(const QVariant& value, int key)
    {
        Q_UNUSED(key);
        Q_UNUSED(value);
    }

signals:
    void itemInteractionChanged();

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
