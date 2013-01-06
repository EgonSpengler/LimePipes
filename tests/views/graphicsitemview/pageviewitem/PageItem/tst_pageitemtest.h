/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QObject>
#include <views/graphicsitemview/pageviewitem/pageitem.h>

class PageItemTest : public QObject
{
    Q_OBJECT
    
public:
    PageItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testAppendRow();
    void testPrependRow();
    void testInsertRow();
    void testRemoveRowIndex();
    void testRemoveRowItem();

private:
    PageItem *m_pageItem;
};
