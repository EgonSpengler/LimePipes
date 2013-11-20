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
#include <QPersistentModelIndex>

class InteractingGraphicsItem;

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
        VisualRootItem,
        VisualScoreItem,
        VisualTuneItem,
        VisualPartItem,
        VisualMeasureItem,
        VisualSymbolItem
    };

    explicit VisualItem(QObject *parent = 0);
    virtual ~VisualItem() {}

    virtual ItemType itemType() const { return NoVisualItem; }
    virtual GraphicalType graphicalType() const { return NoGraphicalType; }

    virtual void setDataFromIndex(const QPersistentModelIndex& index)
    {
        Q_UNUSED(index);
    }

    virtual InteractingGraphicsItem *inlineGraphic() const
    {
        return 0;
    }

    virtual QList<InteractingGraphicsItem*> rowGraphics() const
    {
        return QList<InteractingGraphicsItem*>();
    }

signals:
    void dataChanged(const QVariant& value, int dataRole);
};

#endif // VISUALITEM_H
