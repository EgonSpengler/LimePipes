/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TST_PAGEVIEWITEMTEST_H
#define TST_PAGEVIEWITEMTEST_H

#include <QObject>

class PageViewItem;

class PageViewItemTest : public QObject
{
    Q_OBJECT
public:
    explicit PageViewItemTest(QObject *parent = 0);
    
private Q_SLOTS:
    void initTestCase();
    void init();
    void cleanup();
    void testInitialPageCount();
    void testRowCount();
    void testPageCount();
    void testRowCountMultipage();
    void testRowAt();
    void testRowCountOfPage();
    void testRowAtMultipage();
    void testInsertRow();
    void testInsertRowMultipage();
    void testInsertRowMultipageHighRow();
    void testPrependRow();
    void testRemoveRow();
    void testRemoveRowMultipage();
    void testRemoveRowMultipageHighRow();
    void testRemoveLastEmptyPage();

private:
    void fillFirstPage();
    
private:
    PageViewItem *m_pageViewItem;
    qreal m_defaultVerticalSpacePerPage;
    qreal m_defaultRowItemHeight;
};

#endif // TST_PAGEVIEWITEMTEST_H
