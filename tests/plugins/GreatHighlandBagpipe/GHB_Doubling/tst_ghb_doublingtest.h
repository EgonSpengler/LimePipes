/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef GHB_DOUBLINGTEST_H
#define GHB_DOUBLINGTEST_H

#include <GreatHighlandBagpipe/ghb_doubling.h>

class GHB_DoublingTest : public QObject
{
    Q_OBJECT
    
public:
    GHB_DoublingTest()
        : m_doubling(0) {}
    
private Q_SLOTS:
    void init();
    void cleanup();
    void testDefaultConstructor();

private:
    GHB_Doubling *m_doubling;
};

#endif
