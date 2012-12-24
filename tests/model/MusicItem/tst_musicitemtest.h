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
#include <rootitem.h>
#include <score.h>
#include <tune.h>
#include <symbol.h>
#include "testmusicitem.h"


class MusicItemTest : public QObject
{
    Q_OBJECT
    
public:
    MusicItemTest()
        : m_parent(0),
          m_child1(0),
          m_child2(0),
          m_child3(0) {}

private slots:
    void init();
    void cleanup();
    void testCreateMusicItem();
    void testNullItemCopyConstructor();
    void testInitData();
    void testItemSupportsWritingOfData();
    void testChildAt();
    void testTakeChild();
    void testParent();
    void testRowOfChild();
    void testChildCount();
    void testHasChildren();
    void testChildrenGetter();
    void testInsertChild();
    void testAddChild();
    void testInsertNoItemTypeChild();
    void testSwapChildren();
    void testType();
    void testChildType();
    void testSetParent();
    void testOkToInsertChild();
    void testAfterWritingDataCallback();
    void testBeforeWritingDataCallback();

private:
    MusicItem *m_parent;
    MusicItem *m_child1;
    MusicItem *m_child2;
    MusicItem *m_child3;

    MusicItem *musicItemFactory(int type) {
        switch(type)
        {
        case MusicItem::NoItemType:
            return new TestMusicItem();
        case MusicItem::RootItemType:
            return new RootItem();
        case MusicItem::ScoreType:
            return new Score();
        case MusicItem::TuneType:
            return new Tune();
        case MusicItem::SymbolType:
            return new Symbol();
        default:
            return new TestMusicItem();
        }
    }
};

#endif
