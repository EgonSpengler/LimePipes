/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QList>
#include <QModelIndexList>
#include <QGraphicsScene>

#include <common/defines.h>
#include <app/applicationinterface.h>

class QGraphicsSceneMouseEvent;
class VisualMusicModel;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);

    VisualMusicModel *visualMusicModel() const;
    void setVisualMusicModel(VisualMusicModel *visualMusicModel);

    Application application() const;
    void setApplication(const Application &application);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
    enum class InsertionMode {
        DragAndDrop,
        SymbolPalette
    };

    GraphicsItemType itemTypeOfGraphicsItem(const QGraphicsItem *item) const;
    QList<QGraphicsItem*> selectedSymbolGraphicsItems();
    QGraphicsItem *symbolGraphicsItemForGlyphItem(QGraphicsItem *glyphItem);
    InsertionMode insertionMode() const;
    void setInsertionMode(const InsertionMode &insertionMode);

    QList<int> m_itemTypes;
    QPointF m_symbolDragStart;
    QModelIndexList m_dragSymbolIndexes;
    VisualMusicModel *m_visualMusicModel;
    Application m_application;
    InsertionMode m_insertionMode;
};

#endif // GRAPHICSSCENE_H
