#include "testabstractvisualitem.h"

TestAbstractVisualItem::TestAbstractVisualItem()
{
}


AbstractVisualItem::Type TestAbstractVisualItem::type() const
{
    return AbstractVisualItem::VisualRootItem;
}

void TestAbstractVisualItem::setDataFromIndex(const QPersistentModelIndex &index)
{
}

void TestAbstractVisualItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void TestAbstractVisualItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void TestAbstractVisualItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}

void TestAbstractVisualItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}
