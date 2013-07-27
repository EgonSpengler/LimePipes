/**
 * @author Thomas Baumann <teebaum@ymail.com>
 * 
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 * 
 */

class PageContentRowItem;

class PageViewInterface {
public:
    virtual int pageCount() const = 0;
    virtual int rowCount() const = 0;
    virtual int rowCountOfPage(int index) const = 0;

    virtual void appendRow(PageContentRowItem *row) = 0;
    virtual void prependRow(PageContentRowItem *row) = 0;
    virtual void insertRow(int index, PageContentRowItem *row) = 0;
    virtual void removeRow(int rowIndex) = 0;

    virtual PageContentRowItem *rowAt(int index) const = 0;

};

