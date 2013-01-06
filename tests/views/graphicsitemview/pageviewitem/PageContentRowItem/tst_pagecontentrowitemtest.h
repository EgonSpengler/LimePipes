/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TST_PAGECONTENTROWITEMTEST_H
#define TST_PAGECONTENTROWITEMTEST_H

#include <QObject>
#include <views/graphicsitemview/pageviewitem/pagecontentrowitem.h>

class PageContentRowItemTest : public QObject
{
    Q_OBJECT
public:
    PageContentRowItemTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultRow();

private:
    PageContentRowItem *m_rowItem;
    
};

#endif // TST_PAGECONTENTROWITEMTEST_H
