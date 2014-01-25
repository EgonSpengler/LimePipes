/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef VISUALITEM_H
#define VISUALITEM_H

#include <QObject>
#include <QList>
#include <QPersistentModelIndex>

class InteractingGraphicsItem;
class ItemInteraction;

class VisualItem : public QObject
{
    Q_OBJECT
public:
    enum GraphicalType {
        NoGraphicalType,        //!< The item has no graphical item
        GraphicalRowType,       //!< The item has one or more graphical items, visible as rows.
                                //!  e.g. score header/footer, stave
        GraphicalInlineType     //!< The item has only one graphical item, it is displayed in a
                                //!< row item parent e.g. measure, symbol
    };

    enum ItemType {
        NoVisualItem,
        VisualScoreItem,
        VisualTuneItem,
        VisualPartItem,
        VisualMeasureItem,
        VisualSymbolItem
    };

    explicit VisualItem(QObject *parent = 0);
    explicit VisualItem(ItemType type, QObject *parent = 0);
    explicit VisualItem(ItemType type, GraphicalType graphicalType, QObject *parent = 0);
    virtual ~VisualItem() {}

    void setItemType(ItemType type) { m_itemType = type; }
    ItemType itemType() const { return m_itemType; }

    void setGraphicalType(GraphicalType graphicalType) { m_graphicalItemType = graphicalType; }
    GraphicalType graphicalType() const { return m_graphicalItemType; }

    void setInlineGraphic(InteractingGraphicsItem *inlineGraphic);
    InteractingGraphicsItem *inlineGraphic() const;

    void appendRow(InteractingGraphicsItem *graphicsItem);
    void removeLastRow();
    QList<InteractingGraphicsItem*> rowGraphics() const;
    int rowCount() const;

    virtual void setData(const QVariant& value, int key);
    virtual void insertChildItem(int index, VisualItem *childItem);

signals:
    void dataChanged(const QVariant& value, int dataRole);
    void rowSequenceChanged();

private:
    void connectItemInteraction(ItemInteraction *itemInteraction);
    void disconnectItemInteraction(ItemInteraction *itemInteraction);
    ItemType m_itemType;
    GraphicalType m_graphicalItemType;
    QList<InteractingGraphicsItem*> m_graphicsItems;
};

#endif // VISUALITEM_H
