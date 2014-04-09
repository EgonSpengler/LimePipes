/**
 * @author Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef INTERACTINGGRAPHICSITEM_H
#define INTERACTINGGRAPHICSITEM_H

#include <QList>
#include <QGraphicsWidget>
#include <common/graphictypes/SMuFL/smufl.h>
#include "graphicsitemtypes.h"
#include <common/itemdataroles.h>

class ItemInteraction;

class InteractingGraphicsItem : public QGraphicsWidget
{
    Q_OBJECT

    friend class InteractingGraphicsItemTest;

public:
    explicit InteractingGraphicsItem(QGraphicsItem *parent = 0);
    virtual ~InteractingGraphicsItem() {}

    int type() const { return LP::View::InteractingGraphicsItem; }

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
     * \brief setData Will be called if the data of the view's model has changed.
     *        If the item has an ItemInteraction assigned, its setData will be called.
     * \param value The new value
     * \param key The key of the value
     */
    virtual void setData(const QVariant& value, int key);

    /*!
     * \brief setGraphicsData Sets the graphics data which is data only used by the view.
     *        This can be the line height of the Staff or the line width of the pen to use.
     * \param value The value to set.
     * \param key The data key to set.
     */
    virtual void setGraphicsData(int key, const QVariant& value);

    /*!
     * \brief graphicsData Returns the graphics data which was set with setGraphicsData.
     * \param key The data key.
     * \return  The value.
     */
    virtual QVariant graphicsData(int key);

    SMuFLPtr smufl() const;
    void setSmufl(const SMuFLPtr &smufl);

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
    SMuFLPtr m_smufl;
};

#endif // INTERACTINGGRAPHICSITEM_H
