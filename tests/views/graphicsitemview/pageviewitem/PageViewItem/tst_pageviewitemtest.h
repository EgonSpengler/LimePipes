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
#include <views/graphicsitemview/pageviewitem/pageviewitem.h>

class PageViewItemTest : public QObject
{
    Q_OBJECT
public:
    explicit PageViewItemTest(QObject *parent = 0);
    
private Q_SLOTS:
    void init();
    void cleanup();
    
};

#endif // TST_PAGEVIEWITEMTEST_H
