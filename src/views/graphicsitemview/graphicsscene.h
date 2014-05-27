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
#include <QGraphicsScene>
#include <common/defines.h>

class QGraphicsSceneMouseEvent;
class VisualMusicModel;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicsScene(QObject *parent = 0);

    VisualMusicModel *visualMusicModel() const;
    void setVisualMusicModel(VisualMusicModel *visualMusicModel);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);

private:
    GraphicsItemType itemTypeOfGraphicsItem(const QGraphicsItem *item) const;
    QList<QGraphicsItem*> selectedSymbolGraphicsItems();
    QGraphicsItem *symbolGraphicsItemForGlyphItem(QGraphicsItem *glyphItem);
    QList<int> m_itemTypes;
    QPointF m_symbolDragStart;
    VisualMusicModel *m_visualMusicModel;
};

#endif // GRAPHICSSCENE_H
