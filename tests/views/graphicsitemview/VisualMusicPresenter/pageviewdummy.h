/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef PAGEVIEWDUMMY_H
#define PAGEVIEWDUMMY_H

#include <QList>
#include <QGraphicsWidget>
#include <graphicsitemview/pageviewinterface.h>

class PageViewDummy : public PageViewInterface
{
public:
    PageViewDummy();


    // PageViewInterface interface
public:
    int pageCount() const;
    int rowCount() const;
    int rowCountOfPage(int index) const;
    void appendRow(QGraphicsWidget *row);
    void prependRow(QGraphicsWidget *row);
    void insertRow(int index, QGraphicsWidget *row);
    void removeRow(int rowIndex);
    QGraphicsWidget *rowAt(int index) const;
    int indexOfRow(QGraphicsWidget *row);

private:
    QList<QGraphicsWidget*> m_graphicWidgets;
};

#endif // PAGEVIEWDUMMY_H
