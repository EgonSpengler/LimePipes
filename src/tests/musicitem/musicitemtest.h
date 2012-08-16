/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#ifndef MUSICITEMTEST_H
#define MUSICITEMTEST_H

#include <QObject>
#include "../autotest.h"

class MusicItem;

class MusicItemTest : public QObject
{
    Q_OBJECT
public:
    explicit MusicItemTest(QObject *parent = 0);
    ~MusicItemTest();
    
private slots:
    void testConstructorAndGetters();
    void testChildAt();
    void testRowOfChild();

private:
    MusicItem *m_parent;
    MusicItem *m_child1;
    MusicItem *m_child2;
    MusicItem *m_child3;
    void resetData();
};

DECLARE_TEST( MusicItemTest )

#endif // MUSICITEMTEST_H
