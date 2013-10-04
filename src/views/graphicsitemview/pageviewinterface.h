/**
 * @author Thomas Baumann <teebaum@ymail.com>
 * 
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 * 
 */

#ifndef PAGEVIEWINTERFACE_H
#define PAGEVIEWINTERFACE_H

class QGraphicsWidget;

class PageViewInterface {
public:
    virtual int pageCount() const = 0;
    virtual int rowCount() const = 0;
    virtual int rowCountOfPage(int index) const = 0;

    virtual void appendRow(QGraphicsWidget *row) = 0;
    virtual void prependRow(QGraphicsWidget *row) = 0;
    virtual void insertRow(int index, QGraphicsWidget *row) = 0;
    virtual void removeRow(int rowIndex) = 0;

    virtual QGraphicsWidget *rowAt(int index) const = 0;

};

#endif // PAGEVIEWINTERFACE_H
