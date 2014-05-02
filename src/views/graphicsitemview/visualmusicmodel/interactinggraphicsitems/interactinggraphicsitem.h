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
    /*!
     * \brief The InteractionMode enum Describes, how this InteractingGraphicsItem handles
     *        events.
     */
    enum InteractionMode {
        None,   //!< No interaction is forwarded to the item interaction
        Direct, //!< This item reacts directly on events. (e.g. mousePressEvent is forwarded
                //!< to the item interaction. This is the default behavior.
        Filter, //!< This item filters only the scene events for other items. Direct events
                //!< aren't forwarded
        Both    //!< Direct and Filter events are forwarded to the interaction item
    };

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

    SMuFLPtr smufl() const;
    void setSmufl(const SMuFLPtr &smufl);

    InteractionMode interactionMode() const;
    void setInteractionMode(const InteractionMode &interactionMode);

signals:
    void itemInteractionChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    virtual void smuflHasChanged(const SMuFLPtr& smufl) {}

private:
    ItemInteraction *m_itemInteraction;
    SMuFLPtr m_smufl;
    InteractionMode m_interactionMode;
};

#endif // INTERACTINGGRAPHICSITEM_H
