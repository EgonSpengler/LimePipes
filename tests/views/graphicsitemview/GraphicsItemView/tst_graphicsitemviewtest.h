/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef TST_GRAPHICSITEMVIEWTEST_H
#define TST_GRAPHICSITEMVIEWTEST_H

#include <QObject>
//#include <views/graphicsitemview/graphicsitemview.h>

class GraphicsItemViewTest : public QObject
{
    Q_OBJECT
public:
    GraphicsItemViewTest();
    
private Q_SLOTS:
    void init();
    void cleanup();
    
};

#endif // TST_GRAPHICSITEMVIEWTEST_H
